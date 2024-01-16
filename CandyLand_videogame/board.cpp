#include "Board.h"

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }

    _player1_position = 0;
    _player2_position = 0; // pr2
}

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    if (position == _player1_position)
    {
        cout << "1";
    }
    else if (position == _player2_position) // p2
    {
        cout << "2";
    }
    else if (position == _player1_position && position == _player2_position) // same tile case
    {
        cout << "1 2";
        // same tile constraint 
    }
    else
    {
        cout << " ";
    }
    cout << " " << RESET;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayerPosition(int new_position, Character &player1)
{
    if(player1.getPlayerNumber()==1)
    {
        if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player1_position = new_position;
        return true;
    }
    return false;
    }
    else{
        if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player2_position = new_position; // p2 set position
        return true;
    }
    return false;
    }
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

int Board::getPlayerPosition(Character &player1) const // pass by reference
{
    if (player1.getPlayerNumber() == 1){
        return _player1_position;
    }
    else{
        return _player2_position; // p2 get player position
    }
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position) // use to check if tile has candy store
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::movePlayer(int tile_to_move_forward, Character &player1)
{
    if(player1.getPlayerNumber() == 1)
    {
        int new_player_position = tile_to_move_forward + _player1_position;
        if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
        {
            return false;
        }
        _player1_position = new_player_position;
        setPlayerPosition(_player1_position, player1);
        return true;
    }
    else{
        int new_player_position = tile_to_move_forward + _player2_position; //player 2
        if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
        {
            return false;
        }
        _player2_position = new_player_position;
        setPlayerPosition(_player2_position, player1);
        return true;
    }
}

//----------------------------------------------------------------------------------------//
int Board::MoveTileCount(string card_color, Character player1) // counts tiles to move based on drawn card color, and current position
{
    int current_position;
    current_position = player1.getPosition();
    if(card_color == "magenta"){
        if (current_position % 3 == 0){
            return 3;
        }
        else if(current_position % 3 == 1){
            return 2;
        }
        else if(current_position % 3 == 2){
            return 1;
        }
    }

    else if(card_color == "green"){
        if (current_position % 3 == 2){
            return 2;
        }
        else if(current_position % 3 == 0){
            return 1;
        }
        else if(current_position % 3 == 1){
            return 3;
        }
    }

    else if(card_color == "blue"){
        if (current_position % 3 == 0){
            return 2;
        }
        else if(current_position % 3 == 2){
            return 3;
        }
        else if(current_position % 3 == 1){
            return 1;
        }
    }

    else if(card_color == "blue_double"){
        if (current_position % 3 == 0){
            return 5;
        }
        else if(current_position % 3 == 2){
            return 6;
        }
        else if(current_position % 3 == 1){
            return 4;
        }
    }

    else if(card_color == "green_double"){
        if (current_position % 3 == 2){
            return 5;
        }
        else if(current_position % 3 == 0){
            return 4;
        }
        else if(current_position % 3 == 1){
            return 6;
        }
    }

    else
    {
        if (current_position % 3 == 2){
            return 4;
        }
        else if(current_position % 3 == 0){
            return 6;
        }
        else
        {
            return 5;
        }
    }
    return -1;
}



    
