


#ifndef BOARD_H
#define BOARD_H


#include <iostream>
#include <vector>

using namespace std;


//Cell struct and constants!
enum cellType {empty , player1, player2};

struct Cell {
    cellType c;
    int row;
    int col;
};

const string red         = "\033[0;31m";
const string green       = "\033[1;32m";
const string yellow      = "\033[1;33m";
const string cyan        = "\033[0;36m";
const string magenta     = "\033[0;35m";
const string reset_color = "\033[0m";


//-----Board Class!--------------------------------------
class Board {
    private:
        vector<vector<Cell>> grid;
        int playerOne, playerTwo, row, col;

    public:
        Board(int row_, int col_);
        ~Board();
        
        //for display
        void displayBoard(vector<Cell> moveList);
        void displayBoard();
        bool ifCellinMoveList(Cell c, vector<Cell> moveList);
        void convertCelltoTile(cellType cell);

        //checking validity of moves
        bool ifValidMove(cellType playerCell, int y, int x);      
        bool ifTrap(Cell cell, int dy, int dx);

        //generates moves for player
        vector<Cell> generateMoves(cellType playerCell);

        //flips Cells and updates the board. they function similar to the functions that validate moves
        void updateBoard(cellType playerCell, int y, int x);
        bool flipCells(cellType playerCell, int y, int x, int dy, int dx);

        //gettters
        const int getRow();
        const int getCol();
        const int getScore(cellType player);


        //for the reversi function!
        void resetBoard(int row, int col);
        bool ifBoardFull();

};


//helper functions

//for boundary checking
bool withinBounds(int r, int c, int yBound, int xBound){
    return((r < yBound && r >= 0) && (c < xBound && c >= 0));
}


//for creating new cells
Cell createCell(cellType c_, int y, int x){
    Cell newCell{c_, y, x};
    return newCell;
}

#endif


