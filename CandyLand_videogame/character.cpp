#include "Character.h"
#include <iostream>
#include <string>
using namespace std;

Character::Character()
{
    _gold = 0;
    _stamina = 0;
    //_char_candies;
    _char_name = "";
    _player_name ="";
    _position = 0;
}
Character::Character(string char_n, string player_n, int s, int g, int pos)
{
    _gold = g;
    _stamina = s;
    //_char_candies;
    _char_name = char_n;
    _player_name = player_n;
    _position = pos;

}
int Character::getPosition(){
    return _position;
}
void Character::setPosition(int pos){
    _position = pos;
}


void Character::setCharacterName(string char_name)
{
    _char_name = char_name;
}
string Character::getCharacterName()
{
    return _char_name;
}

void Character::setGold(int gold)
{
    _gold = gold;
}
int Character:: getGold()
{
    return _gold;
}

int Character::getStamina()
{
    return _stamina;
}
void Character::setStamina(int stamina)
{
    _stamina = stamina;
}

vector<Candy> Character::getCharCandies()
{
    return _char_candies;
}
void Character::setCharCandies(vector<Candy> char_candies)
{
    _char_candies = char_candies;
}

void Character::setPlayerName(string player_name)
{
    _player_name = player_name;
}
string Character::getPlayerName()
{
    return _player_name;
}

void Character::setPlayerNumber(int p){
    player_number = p;
}
int Character::getPlayerNumber(){
    return player_number;
}

