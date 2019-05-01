
#include "Board.h"
#include <iostream>

Board::Board(int row_, int col_)
:row(row_),col(col_)
{
    resetBoard(row, col);
}

Board::~Board(){}


//two different display functions

//for general use
void Board::displayBoard(){
    cout << "\n";

    //for writing the column letters
    cout << "  ";
    for(int i = 0; i < col; i++){
        cout << char('A' + i) << " ";
    }
    cout << "\n";

    //goes through each cell in the grid
    for(int i = 0; i < row; i++){
        //for writing row numbers
        cout << i + 1 << " ";
        for(int j = 0; j < col; j++){
            convertCelltoTile(grid[i][j].c);
        }
        cout << "\n";
    }

    //to display the current score
    cout << "\n";
    cout << "Player 1: " << playerOne << " Player 2: " << playerTwo << "\n";
}

//for the user controlled player
void Board::displayBoard(vector<Cell> moveList){
    cout << "\n";
    cout << "  ";

    for(int i = 0; i < col; i++){
        cout << char('A' + i) << " ";
    }
    cout << "\n";

    for(int i = 0; i < row; i++){
        cout << i + 1 << " ";
        for(int j = 0; j < col; j++){

            //highlights moves that are valid for the player
            if(ifCellinMoveList(grid[i][j], moveList)){
                cout << red;
            }
            convertCelltoTile(grid[i][j].c);
            
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "Player 1: " << playerOne << " Player 2: " << playerTwo << "\n";
}

//helper for the display for the user-controlled player
bool Board::ifCellinMoveList(Cell c, vector<Cell> moveList){
    for(Cell c_ : moveList){
        if(c_.row == c.row && c_.col == c.col){
            return true;
        }
    }
    return false;
}


//converts the passed cellType to either a 0, 1, 2 based on it's type
void Board::convertCelltoTile(cellType cell){
    switch(cell){
        case empty:
            cout << 0 << reset_color << " ";
            break;
        case player1:
            cout << green << 1 << reset_color << " ";
            break;
        case player2:
            cout << cyan << 2 << reset_color << " ";
            break;
        default:
            break;
    }
}

//-------------following functions validate the moves--------------------
bool Board::ifValidMove(cellType playerCell, int y, int x){

    //checks if the current cell is actuall empty
    if(grid[y][x].c == empty){

        //checks around cell
        int r, c;
        Cell adjCell;

        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){

                if(i != 0 || j != 0){
   
                    r = y + i;
                    c = x + j;

                    //if the adjacent cell is within bounds
                    if(withinBounds(r, c, row, col)){

                        adjCell = grid[r][c];

                        //checks if the adjacent cell is of the other player
                        if(adjCell.c != playerCell && adjCell.c != empty){

                            //checks if that adjacent cell is trapped within the players cell
                            if(ifTrap(adjCell, i, j)){
                                return true;
                            }

                        }
                    }
                }
            }
        }

        //returns false if the empty move is not valid
        return false; 
    }
    else{

        //reaches this point if it isn't an empty cell
        return false;
    }    
}

bool Board::ifTrap(Cell cell, int dy, int dx){


    //checks the following cell at a certain direction to see if is within bounds
    if(withinBounds(cell.row + dy, cell.col + dx, row, col)){

        Cell adjCell = grid[cell.row + dy][cell.col + dx];

        //base cases, if the following cell is either empty or another player cell
        if(adjCell.c == empty){
            return false;
        }
        else if (adjCell.c != cell.c){
            return true;
        }

        //recursive case, if the following cell is of equal cell type
        else{
            return ifTrap(adjCell, dy, dx);
        } 
    }  
    else{
        //reaches here if following cell is not in bound
        return false;
    }
}

//-----------a function in which returns the amount of valid cells that a player(defined by cellType) can make---------
vector<Cell> Board::generateMoves(cellType playerCell){

    vector<Cell> moveList;

    for(vector<Cell> row : grid){
        for(Cell cell : row){
            if(ifValidMove(playerCell, cell.row, cell.col)){
                moveList.push_back(cell);
            }
        }
    }
    return moveList;
}


//------------------functions here update the board once the player has made a decision, 
//these functions are similar to the valid moves ----------------------------------------------------------------------
void Board::updateBoard(cellType playerCell, int y, int x){

    //boundary checking shouldn't be done here, since this function is only called for valid moves.
    grid[y][x].c = playerCell;


    //checks surrounding cells
    int r, c;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            
            if(j!= 0 || i!= 0){ 

                r = y + i;
                c = x + j;

                //if adjacent cell is within bounds
                if(withinBounds(r, c, row, col)){
                    if(grid[r][c].c != playerCell && grid[r][c].c != empty){
                        //flips cells
                        flipCells(playerCell, r, c, i, j);
                    }
                }
            }    
        }
    }

    //the following updates the score
    int numPlayer1Cells, numPlayer2Cells;
    numPlayer1Cells = numPlayer2Cells = 0;
    for(vector<Cell> row: grid){
        for(Cell cell : row){
            if(cell.c == player1){
                numPlayer1Cells++;
            }
            else if(cell.c == player2){
                numPlayer2Cells++;
            }
        }
    }

    playerOne = numPlayer1Cells;
    playerTwo = numPlayer2Cells;
}

bool Board::flipCells(cellType playerCell, int y, int x, int dy, int dx){

    //checks the passed x and y coordinates of the cell to see if it is within bounds
    if(withinBounds(y, x, row, col)){
        Cell cell = grid[y][x];

        //base cases: if current cell is empty or of the other player
        if(cell.c == empty){
            return false;
        }

        else if(cell.c == playerCell){
            return true;
        }
        //recursive case
        else{
            //sort of like the ifTrap function, only this time we flip the cell if it is trapped
            if(flipCells(playerCell, y + dy, x + dx, dy, dx)){
                cell.c = playerCell;
                return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        return false;
    }
}

//getters
const int Board::getRow(){
    return row;
}

const int Board::getCol(){
    return col;
}

const int Board::getScore(cellType player){
    switch(player){
        case player1:
            return playerOne;
        case player2:
            return playerTwo;
        default:
            return 0;
    }
}

bool Board::ifBoardFull(){
    return((playerOne + playerTwo) == (row * col));
}

//for reseting the board
void Board::resetBoard(int row, int col){
    grid.clear();
    vector<Cell> tempRow;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            tempRow.push_back(createCell(empty, i, j));
        }
        grid.push_back(tempRow);
        tempRow.clear();
    }

    //Othello configuration
    grid[3][3].c = player1;
    grid[3][4].c = player2;
    grid[4][3].c = player2;
    grid[4][4].c = player1;


    playerOne = playerTwo = 2;
}

