#include "Board.h"
#include "Character.h"
#include "Candystore.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void displayCharacters(string char_choice, vector<Character> &characters);

int main()
{
    Candystore store;
    Candystore store1;
    Candystore store2;

    Candystore treasure;
    Candystore treasure1;
    Candystore treasure2;

    Board board;
    Board board1;
    board.displayBoard();

    // sets 3 candy stores on the game
    store.setCandyStorePosition(store, 0);
    store1.setCandyStorePosition(store1, 1);
    store2.setCandyStorePosition(store2, 2);
    //sets 3 treasures on game
    treasure.setTreasurePosition(treasure, 0);
    treasure1.setTreasurePosition(treasure, 1);
    treasure2.setTreasurePosition(treasure, 2);

    //read from candies txt, and store elements in candy object
    ifstream candyFile("candies.txt");
    if(!candyFile.is_open())
    {
        cout << "error loading file" << endl;
        //restart program
        return 0;
    }
    vector<Candy> candies;
    string line;
    while(getline(candyFile, line))
    {
        Candy candy;
        stringstream tokenStream(line);
        string token;
        int index = 0;
        while(getline(tokenStream,token,'|'))
        {
            switch(index)
            {
                case 0:
                    candy.name = token;
                    break;
                case 1:
                    candy.description = token;
                    break;
                case 2:
                    candy.effect_type = token;
                    break;
                case 3:
                    candy.effect_value = stoi(token);
                    break;
                case 4:
                    candy.candy_type = token;
                    break;
                case 5:
                    candy.price = stoi(token);
                    break;
                default:
                    break;
            }
        index++;
        }
        candies.push_back(candy);
    }
    candyFile.close();
//--------------------------------------------------------------------------------------------//
    //Loading character objects from characters.txt
    vector<Character> characters;
    ifstream charFile("characters.txt");
    if (charFile.is_open()) {
        Character character;
        string line;
        while (getline(charFile, line)) {
            stringstream tokenStream(line);
            string token;
            int index = 0;
            while (getline(tokenStream, token, '|')) {
                switch (index) {
                    case 0:
                        character.setCharacterName(token);
                        break;
                    case 1:
                        character.setStamina(stoi(token));
                        break;
                    case 2:
                        character.setGold(stoi(token));
                        break;
                    case 3:
                        stringstream candyStream(token);
                        string candy;
                        vector<Candy> candies;
                        while (getline(candyStream, candy, ',')) {
                            Candy candyObject; 
                            candyObject.name = candy; 
                            candies.push_back(candyObject); 
                        }
                        character.setCharCandies(candies); 
                        break;
                }
                index++;
            }
            characters.push_back(character);
        }
        charFile.close();
    //return characters;
    } 
    else 
    {
        cout << "Error loading file" << endl;
        return 0;
    }
//------------------------------------------------------------------------------//
    cout << "Welcome to the game of Candyland. Please enter number of participants:" << endl;
    int num_players;
    cin >> num_players;

    string player_name; 
    
    Character player1; 
    Character player2;
    
    string char_choice = "";
    Game game;
    for(int i = 0; i < num_players; i++)
    {
        switch(i)
        {
            case 0:
                cout << "Enter player name:" << endl;
                cin >> player_name;
                //Character player1;
                char choice;
                
                player1.setPlayerName(player_name);
                cout << "Awesome! Here is a list of characters a player can select from:" << endl;
                //characters = loadCharacters();
                displayCharacters(char_choice, characters);
                cout << "The selected Character is: " << endl;
                cin >> char_choice;

                for (auto& character : characters) {
                if (character.getCharacterName() == char_choice) {
                    player1 = character;  // assigns entire character to player1
                    player1.setPlayerNumber(i+1);
                    break;
                }
                }
                cout << "Do you want to visit the candy store? (y/n)" << endl;
                cin >> choice;
                choice = tolower(choice); 
                if (choice == 'y')
                {
                    //display candy store
                    store.displayCandyStore(candies, player1);
                    
                }
                // if enters no, start turn
                game.turn(player1, board1, game, candies);
                

                break; 

            case 1:
                cout << "Enter player name:" << endl;
                cin >> player_name;
                //Character player2;
                player2.setPlayerName(player_name);
                cout << "Awesome! Here is a list of characters a player can select from:" << endl;
                //characters = loadCharacters();
                displayCharacters(char_choice, characters);
                cout << "The selected Character is: " << endl;
                cin >> char_choice;

                for (Character character : characters) {
                if (character.getCharacterName() == char_choice) {
                    player2 = character;  // Assign the entire character to player1
                    break;
                }
                }

                //player2.setCharacterName(char_choice);
                cout << "Do you want to visit the candy store? (y/n)" << endl;
                cin >> choice;
                choice = tolower(choice); 
                if (choice == 'y')
                {
                    // enter candy store
                    store.displayCandyStore(candies, player2);
                }
                game.turn(player2, board, game, candies);
                
                break; 
        }
        board.displayBoard();
    }

    bool result;
    while(result == false){
        cout << "player 1's turn:" << endl;
        game.turn(player1, board, game,candies); // enters player1's turn

        int newPos = board.getPlayerPosition(player1);
        bool result3 = board.isPositionCandyStore(newPos); // checks if player1 position is on candy store
        cout << result3 << endl;
        if(result3 == true){
            store.displayCandyStore(candies, player1);
        }

        
        result = game.checkWin(board, player1, player2, num_players); // checks if player 1 after turn
            if(num_players > 1){
                cout << "Player 2's turn" << endl;
                game.turn(player2, board, game, candies);// enters player 2 turn
                 // displays board after turn
                result = game.checkWin(board, player1, player2, num_players); // checks if player 1 after turn
            }
        board.displayBoard();
        
    }
    return 0;
}
//------------------------------------------------------------------------------//
//function to display character list , and all their stats
void displayCharacters(string char_choice, vector<Character> &characters)
{
    int size_of_vector = characters.size();
    for(int i = 0; i < size_of_vector; i++)
    {
        if(characters[i].getCharacterName() == char_choice)
        {
            characters.erase(characters.begin() + i);
        }
        else
        {
            cout << "Name:" << characters[i].getCharacterName() << endl;
            cout << "Stamina:" << characters[i].getStamina() << endl;
            cout << "Gold:" << characters[i].getGold() << endl;
            cout << "Candies:" << endl;
            vector<Candy> charCandies = characters[i].getCharCandies();
            int charCandySize = charCandies.size();
            //displays candies names from list
            for(int j = 0; j < charCandySize; j++ )
            {
                cout << charCandies[j].name << endl;
            }
            cout << "-------------------------------" << endl;
        }
    }
}
//------------------------------------------------------------------------------//
