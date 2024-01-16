#include "Candystore.h"
#include "Character.h"
#include "game.h"
#include <iostream>
#include <vector>
using namespace std;
// candy store
void Candystore::displayCandyStore(vector<Candy>candies, Character player1)
{
    cout << "Here is a list of candies in the candystore:" << endl;
    displayAvailableCandies(candies);
    cout << "Which candy would you like to buy?" << endl;
    Candy candy_choice;
    cin >> candy_choice.name;
    //might need an object here
    Game purchase;
    bool check = purchase.verifyPurchase(candy_choice, player1);
    if(check == true)
    {
        cout << "true" << endl;

    }
    else   
    {
        cout << "false" << endl;
    }
    
}  
 // candy store helper function
void Candystore::displayAvailableCandies(const vector<Candy>&candies)
{
    // randomly choose 3 candies from the candies vector 
    
    srand(static_cast<unsigned>(time(nullptr)));
    vector<Candy>candy;
    
    // Generate and print 3 random numbers
    for(int i = 0; i < 3; i++)
    {
        int random_number = rand() % candies.size();
        candy.push_back(candies[random_number]);
    }
    //display candies:
    int candy_size = candy.size();
    for(int j = 0; j < candy_size; j++)
    {
        cout << "Name:" << candy[j].name << endl;
        cout << "Description:" << candy[j].description << endl;
        cout << "Effect:"<< candy[j].effect_type << endl;
        cout << "Effect value:" << candy[j].effect_value << endl;
        cout << "Candy type:"<< candy[j].candy_type << endl;
        cout << "Price:"<< candy[j].price << endl;
        cout << "-----------------------------------------" << endl;
    }
}



void Candystore::setCandyStorePosition(Candystore &store, int candyStoreNum)
{
    //this function uses random number generator to randomly set a candy store on a magenta tile 
    //in the first 27 tiles, green on 28-54, and blue on 54-81
    srand(static_cast<unsigned int>(time(0)));
    
        switch(candyStoreNum)
        {
            case 0:{
                // 0-27 magenta
                // 0, 3, 6, ...
                vector<int>position1 = {0,3,6,9,12,15,18,21,24,27};
                int randomIndex = rand() % position1.size();
                int selectedPosition1 = position1[randomIndex];
                store.setStore(selectedPosition1);
                break;
                
            }
            case 1:{
                //28 - 54 green
                // 1, 4, 7, ....
                vector <int>position2 = {29, 32, 35, 38, 41, 44, 47, 50, 53};
                int randomIndex = rand() % position2.size();
                int selectedPosition2 = position2[randomIndex];
                store.setStore(selectedPosition2);
                break;
            }
            case 2:{
                //55 - 81 blue
                // 2, 5, 8, ...
                vector <int>position3 = {57,60,63,66,69,72,75,78,81};
                int randomIndex = rand() % position3.size();
                int selectedPosition3 = position3[randomIndex];
                store.setStore(selectedPosition3);
                break;
            }
        }
   // }
}

void Candystore::setStore(int pos){
    _position = pos;
}

int Candystore::getStore(){
    return _position;
}


void Candystore::setTreasurePosition(Candystore &treasure, int treasure_num){
    srand(static_cast<unsigned int>(time(0)));
    // this function uses a random number generator to set 3 hidden treasures on the board, one in the first 27 tiles, another in
    //first 54, and another between 81
        switch(treasure_num)
        {
            case 0:{
                // 0-27 magenta
                // 0, 3, 6, ...
                int randomNumber = rand() % 27;
                treasure.setTreasure(randomNumber);
                break;
                
            }
            case 1:{
                //28 - 54 green
                // 1, 4, 7, ....
                int randomNumber1 = rand() % 54;
                treasure.setTreasure(randomNumber1);
                break;
            }
            case 2:{
                //55 - 82 blue
                // 2, 5, 8, ...
                int randomNumber2 = rand() % 81;
                treasure.setTreasure(randomNumber2);
                break;
            }
        }
    //}
}
void Candystore::setTreasure(int pos){
    _TreasurePosition = pos;
}
int Candystore::getTreasure(){
    return _TreasurePosition;
}