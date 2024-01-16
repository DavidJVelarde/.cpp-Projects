#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

#include "character.h"
//#include "game.h"

#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;



struct Tile
{
    string color;
    string tile_type;
};


class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;
    int _player1_position;
    int _player2_position;

public:
    Board();

    void resetBoard();
    void displayTile(int);
    void displayBoard();

    bool setPlayerPosition(int, Character &player1);

    int getBoardSize() const;
    int getCandyStoreCount() const;

    int getPlayerPosition(Character &player1) const;

    bool addCandyStore(int);
    bool isPositionCandyStore(int); 

    bool movePlayer(int tile_to_move_forward, Character &player1);


    int MoveTileCount(string card_color, Character player1);

//getters for tile type/color
    string getTileColor(int position) const 
    {
        if (position >= 0 && position < _BOARD_SIZE) 
        {
            return _tiles[position].color;
        }
        return "";  
    }

    // new method to get a Tile object at a specific position
    string getTileType(int position) 
    {
        srand(static_cast<unsigned int>(time(0)));  

        if (position >= 0 && position < _BOARD_SIZE) {
            int randomNumber = rand() % 100;  

            // 25% chance to return "special tile"
            if (randomNumber < 25) {
                return "special tile";
            } 
            // 75% chance to return "regular tile"
            else {
                return "regular tile";
            }
        }
        return "";
    }

    
};



#endif