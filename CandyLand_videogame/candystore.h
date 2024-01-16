#ifndef CANDYSTORE_H
#define CANDYSTORE_H

#include <vector>
#include "Candy.h"

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
class Character;

class Candystore 
{
    private:
        int _position;

        int _TreasurePosition;
    public:
        // Candystore();
        // Candystore( int _position, int _TreasurePosition);
        void displayCandyStore(vector<Candy> candies, Character player1);
        void displayAvailableCandies(const vector<Candy>& candies);

        void setCandyStorePosition(Candystore &store, int store_num);

        void setStore(int pos);
        int getStore();

        void setTreasurePosition(Candystore &treasure, int treasure_num);

        void setTreasure(int pos);
        int getTreasure();
};



#endif
