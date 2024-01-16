#ifndef CHARACTER_H
#define CHARACTER_H
#include "candy.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Character
{
    private:
        int _gold;
        int _stamina;
        vector<Candy> _char_candies;
        string _char_name;
        string _player_name;
        int player_number;

        int _position;

    public:
        Character();
        Character(string char_n, string player_n, int s, int g, int pos);

        string getPlayerName();
        void setPlayerName(string player_name);

        int getStamina();
        void setStamina(int stamina);

        int getGold();
        void setGold(int gold);

        vector<Candy> getCharCandies();
        void setCharCandies(vector<Candy> char_candies);

        string getCharacterName();
        void setCharacterName(string char_name);

        //void displayInventory(vector<string>_char_candies); //******************

        //vector<Character> loadCharacters();
        int getPosition();
        void setPosition(int pos);
        
        void setPlayerNumber(int p);
        int getPlayerNumber();

};

#endif