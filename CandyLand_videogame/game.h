#ifndef GAME_H
#define GAME_H

#include "Character.h"
#include "Candystore.h"
#include "Board.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

class Game
{
	private:
		Board gameBoard;
		Candystore store;
		string deck[3];

		int _player_count;
		string char_choice;

	public:
		void loadCandies();
		void loadCharacters();

		void displayCharacterMenu();
		void displayCharacters();

		void displayMainMenu();

		 // -> each player has a turn ->draw cards from deck array
		//1. draw a card
		//if player draws card, 40% calamity chance
		//2. use a candy
		// 3. show stats

		void checkTile();
		void getPlayers(); 
		void setPlayers();
		void getNames();
		void setNames();

		bool verifyPurchase(Candy candy_choice, Character player1);
		void turn(Character& player1, Board &board, Game game,vector<Candy> candies);
		bool verifyStamina(Character player1);

		string drawCard();
		bool calamity();
		void pickCalamity(Character &player1);

		void displayStats(Character player1);

		void useCandy();

		bool playRockPaperScissors();
		
		bool checkWin(Board board, Character player1, Character player2, int num_players);

		

};

#endif