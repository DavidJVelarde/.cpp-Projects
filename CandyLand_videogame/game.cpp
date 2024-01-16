#include "Game.h"
#include <iostream>
#include <vector>
using namespace std;
// function to verify purchase, after player buys candy from candy store
bool Game::verifyPurchase(Candy candy_choice, Character player1)
{
    if (player1.getGold() >= candy_choice.price)
    {
        cout << "returns true" << endl;
        return true;
    }
    
    else
    {
        cout << "your broke, you dont have enough gold, pick again." << endl;
        return false;
    } 
}
// turn function, called for players when its their turn.
void Game::turn(Character &player1, Board &board, Game game, vector<Candy> candies)
{
    int stamina = player1.getStamina();
    stamina = stamina -1;
    player1.setStamina(stamina);

    if(player1.getStamina() <= 0)
    {
        //player misses out on 2 turns
    }
    else if(player1.getStamina() >0)
    {
        cout << "Please select a menu option:" << endl;
        cout << "1. Draw a Card" << endl;
        cout << "2. Use Candy" << endl;
        cout << "3. show player stats" << endl;
        int menu_choice;
        cin >> menu_choice;
        switch(menu_choice)
        {
            case 1:
            {//draw a card
                string card;
                char choice;
                //Board board;
                cout << "To draw a card press D" << endl;
                cin >> choice;
                if (choice == 'D')
                {
                    //draws a card for player, moves player to the position based on drawn card.
                    card = drawCard();
                    cout << card << endl;
                    int tiles_to_move = board.MoveTileCount(card,player1);
                    int initialPos = board.getPlayerPosition(player1);
                    board.movePlayer(tiles_to_move, player1);//updates player pos
                    board.setPlayerPosition(initialPos + tiles_to_move, player1);
                    

                    //int secondPosition = gameBoard.getPlayerPosition(); // captures new position
                    int newPos = board.getPlayerPosition(player1); // Get updated position
                    
                    // checks if current position is a regular tile, if so
                    //possible chance for calamity to occur, calls calamity() functions to check.
                    if (board.getTileType(newPos) == "regular tile") { 
                        cout <<board.getTileType(newPos) << endl;
                        bool T_F = calamity();
                        if (T_F) {
                            pickCalamity(player1);
                        }
                    }
                    else{
                        // if current tile player is on, isnt a regular tile, it is a special tile, and 
                        //implements chances for each special case, if it is special tile.
                        cout << "special tile"<< endl;
                        int randomNumber = rand() % 100;
                        if (randomNumber < 25) {
                            //shortcut
                            cout << "you landed on a special shortcut tile" << endl;
                            board.movePlayer(4, player1);
                            //check for candy store*******************
                        }
                    
                        else if(randomNumber < 50 && randomNumber > 25){
                            //IceCream stop
                            cout << "you landed on a special IceCream stop tile, heres another turn:"<< endl;
                            card = drawCard();
                            cout << card << endl;
                            int tiles_to_move = board.MoveTileCount(card,player1);
                            board.movePlayer(tiles_to_move, player1);
                            //check for candy store********************

                        }
                        else if(randomNumber <75 && randomNumber >50){
                            //gumDrop Forest
                            cout << "you landed on a special gumDrop Forest Tile, move 4 tiles back" << endl;
                            board.movePlayer(-4, player1);
                            int newPos1 = board.getPlayerPosition(player1);
                            if (newPos1 < 0){
                                board.setPlayerPosition(0, player1);
                            }
                            int gold = player1.getGold();
                            int randN = rand() % 10;
                            gold = gold -randN;
                            cout << "you lost "<< randN << "gold"<< endl;
                            player1.setGold(gold);
                        }
                        else{

                            //Gingerbread house
                            cout << "you landed on a special GingerBread House tile" << endl;
                            // send player back to inition position

                            board.movePlayer(board.getPlayerPosition(player1) - tiles_to_move, player1);
                            

                        }
                    }

                    //get candysotre candies
                    // checks if current position is a candystore, if it is, player enters.
                    bool result3 = board.isPositionCandyStore(newPos);
                    cout << result3 << endl;
                    if(result3 == true){
                        store.displayCandyStore(candies, player1);
                    }
                }
                else
                {
                    // invalid input case
                    cout << "invalid input" << endl;
                    
                }
                break;
            }
            case 2:
            { //use a candy
            //displays list of candies in inventory
                vector<Candy>candies;
                candies = player1.getCharCandies();
                cout << "Here is a list of your candies:" << endl;
                int candies_size = candies.size();
                for(int i = 0; i<candies_size;i++)
                {
                    cout << candies[i].name << endl;
                }
                useCandy();
                break;
            }
		    case 3:
            {// show stats
            // displays player stats, and recursively calls the turn function 
            // so player can have the option to draw a card after checking stats.
                cout << "Here are your stats:" << endl;
                displayStats(player1);
                game.turn(player1, board, game, candies);
                break;
            }
        }           
    }
        //after moving, update position on board
}

// draw a card function to randomly select a card color, returns card string
string Game::drawCard()
{
    srand(static_cast<unsigned>(time(nullptr)));
    vector<string>cards = {"magenta", "green", "blue"};
    vector<string>cards_double = {"magenta_double", "green_double", "blue_double"};
    
    // generate and print 3 random numbers
    string card;
    for(int i = 0; i < 3; i++)
    {
        int random_number = rand() % cards.size();
        card = cards[random_number];
        if ((rand() % 100) < 20) 
        {
            card = cards_double[random_number];
        }
    }
    return card;
}
// calamity 40% chance function
bool Game::calamity()
{
    //srand(static_cast<unsigned>(time(nullptr)));
    int random_number = rand() % 100;
    return random_number < 40;

}
// function picks calamity, if first calamity function is true
void Game::pickCalamity(Character &player1) 
{
    int random_number = rand() % 100;  

    if (random_number < 30) {
        cout << "Oh no! Candy Bandits have swiped your gold coins!" << endl;
        int gold = player1.getGold() - (rand() % 10 + 1);
        player1.setGold(gold);

    } else if (random_number < 65) {
        cout << "Oh dear! You got lost in the lollipop labyrinth!" << endl;
        // player loses out on 1 turn 
        bool decision = playRockPaperScissors();
        if (decision == true){
            cout << "you won a turn back" << endl;
            //+1 turn
        }
    } else if (random_number < 80) {
        cout << "Watch out! A candy avalanche has struck!" << endl;
        int stamina = player1.getStamina() - (rand() % 10 + 5);
        player1.setStamina(stamina);
        //player loses 1 turn
        bool decision = playRockPaperScissors();
        if (decision == true){
            cout << "you won a turn back" << endl;
            //+1 turn
        }
    } else {
        cout << "Oops! You are stuck in a sticky taffy trap!" << endl;
        // -1 turn()
        // if player has a Magical Candy, 
        //+1 turn

    }
}
// fucntion to display player stats
void Game::displayStats(Character player1)
{
    cout << "Player Name: " << player1.getPlayerName() << endl;
    cout << "Character Name: " <<player1.getCharacterName() << endl;
    cout << "Stamina: " <<player1.getStamina() << endl;
    cout << "Gold: " <<player1.getGold() << endl;
    vector<Candy>candies;
    candies = player1.getCharCandies();
    cout << "Here is a list of your candies:" << endl;
    int candies_size = candies.size();
    for(int i = 0; i<candies_size;i++)
    {
        cout << candies[i].name << endl;
    }

}
// function for player to use candy during turn
void Game::useCandy()
{
    
    cout << "Enter a Candy you wish to use:" << endl;
    string candy_name;
    cin >> candy_name;
    
    getline(cin, candy_name); 

    Candy choice;
    choice.name = candy_name; 

    if(choice.effect_value < 0)
    {
        cout << "Do you want to use " << choice.name << " candy against your opponent?(y/n)" << endl;
        char choice1;
        cin >> choice1;
        if(choice1 == 'y'){

            // use against opponent 
        }
    }
    else
    {
        cout << "Do you want to use " << choice.name << " candy on yourself?(y/n)" << endl;
        char choice1;
        cin >> choice1;
        if(choice1 == 'y'){
            // use to aid yourself
        }
    }                
}


bool Game::playRockPaperScissors() 
{
    srand(static_cast<unsigned int>(time(0)));

    const int ROCK = 1;
    const int PAPER = 2;
    const int SCISSORS = 3;

    int userChoice;
    cout << "Choose your move: (1-3)" << endl;
    cout << "1. Rock" << endl;
    cout << "2. Paper" << endl;
    cout << "3. Scissors" << endl;
    cin >> userChoice;

    if (userChoice < ROCK || userChoice > SCISSORS) {
        cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        return false;
    }
 
    int computerChoice = rand() % 3 + 1;

    string choices[4] = {"", "Rock", "Paper", "Scissors"};
    cout << "You chose " << choices[userChoice] << endl;
    cout << "Computer chose " << choices[computerChoice] << endl;

    if (userChoice == computerChoice) {
        cout << "It's a tie!" <<endl;
    } else if ((userChoice == ROCK && computerChoice == SCISSORS) ||
               (userChoice == PAPER && computerChoice == ROCK) ||
               (userChoice == SCISSORS && computerChoice == PAPER)) {
        cout << "You win!" << endl;
        return true;
               }
    cout << "Computer wins!" << endl;
    return false;
}
// function called after player turn, and position is updated.
bool Game::checkWin(Board board, Character player1, Character player2, int num_players){
    
    //cout << "player position:" << board.getPlayerPosition(player1)<< endl;
    if ((board.getPlayerPosition(player1) >= 82)||(board.getPlayerPosition(player2) >= 82))
    {
        if(board.getPlayerPosition(player1)>board.getPlayerPosition(player2)){
        cout << "congrats " << player1.getPlayerName()<< "you win!!!!" << endl;
        }
        else
        {
            cout << "congrats " << player2.getPlayerName()<< "you win!!!!" << endl;
        }
        displayStats(player1);
        if(num_players >1){
            displayStats(player2);
        }

        //upload player stats to results.txt
        ofstream outFile;
        outFile.open("results.txt");

        outFile << "Player Name: " << player1.getPlayerName() << endl;
        outFile << "Character Name: " <<player1.getCharacterName() << endl;
        outFile << "Stamina: " <<player1.getStamina() << endl;
        outFile << "Gold: " <<player1.getGold() << endl;
        vector<Candy>candies;
        candies = player1.getCharCandies();
        cout << "Here is a list of your candies:" << endl;

        int candies1_size = candies.size();
        for(int i = 0; i<candies1_size;i++)
        {
            outFile << candies[i].name << endl;
        }
            if (num_players > 1)
            outFile << "------------------------------" << endl;
            outFile << "Player Name: " << player2.getPlayerName() << endl;
            outFile << "Character Name: " <<player2.getCharacterName() << endl;
            outFile << "Stamina: " <<player2.getStamina() << endl;
            outFile << "Gold: " <<player2.getGold() << endl;
            vector<Candy>candies2;
            candies2 = player2.getCharCandies();
            cout << "Here is a list of your candies:" << endl;
            int candies2_size = candies2.size();
            for(int i = 0; i<candies2_size;i++)
            {
                outFile << candies2[i].name << endl;
            }
            outFile.close();

            return true;
    }
    return false;
}

