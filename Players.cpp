
#include "Players.h"


Player::~Player(){}

//-------------------------------------------USER---------------------------------------------------------------


User::User(cellType c)
:playerCell(c)
{}

void User::determineMove(Board& board){
    //generates user moves
    moveList = board.generateMoves(playerCell);

    //only if there are valid moves
    if(moveList.size() > 0){

        //display board
        board.displayBoard(moveList);

        //prompts user to enter a move
        string input;
        cout << "Enter a move! ";

        getline(cin , input);
        toLower(input);

        //a while loop to keep checking if the input is correct
        while(!ifValidInput(input, board)){
            getline(cin , input);
            toLower(input);
        } 

        //update board
        board.updateBoard(playerCell, move[0], move[1]);
    }

    else{
        //reaches this point if it can't make a move
        cout << "User unable to make a move!" << "\n";
    }
}




//validates input
bool User::ifValidInput(string& input, Board& board){

    //checks if user input is of valid format
   if(input.size() == 2 && (isalpha(input[1]) && isdigit(input[0]))){
       int r = input[0] - 49;
       int c = input[1] - 'a';

        //following checks if the input is within bounds
       if(withinBounds(r, c, board.getRow(), board.getCol())){
           //checks to see if it matches any of the moves in the movelist
           for(int i = 0; i < moveList.size(); i++){
               if(moveList[i].row == r && moveList[i].col == c){
                   move[0] = moveList[i].row;
                   move[1] = moveList[i].col;
                   return true;
               }
           }

            //reaches this point if the move is not valid
           cout << "move is not valid!" ; 
           return false;

       }
       else{
           //for out of bounds move
           cout << "move is out of bounds!";
           return false;
       }
   }
   else{

       //invalid syntax
       cout << "Invalid syntax for entering move! please enter the row # and the character of the column! (ex. 5a)";
       return false;
   }
}

//getters
const cellType User::getCellType(){
    return playerCell;
}

bool User::ifNoMoves(){
    return moveList.empty();
}

//-------------------------------------------COMPUTER-----------------------------------------------------------

Computer::Computer(cellType c)
:computerCell(c)
{}

void Computer::determineMove(Board& board){
    //generates computer moves
    moveList = board.generateMoves(computerCell);
    if(moveList.size() > 0){

        cout << "Computer turn!" << "\n";
        board.displayBoard();

        //intially chooses a random move
        int randomMove = rand() % moveList.size();
        move[0] = moveList[randomMove].row;
        move[1] = moveList[randomMove].col;

        for(Cell c: moveList){

            //if it finds a move in a movelist that is at the corner, it sets the move to that and breaks out of the loop
            if((c.row == 0|| c.row == board.getRow() - 1) && (c.col == 0|| c.col == board.getCol() - 1)){
                move[0] = c.row;
                move[1] = c.col;
                break;
            }
            //if it finds a move that is at the side
            else if((c.row == 0|| c.row == board.getRow() - 1) || (c.col == 0 || c.col == board.getCol() - 1)){
                move[0] = c.row;
                move[1] = c.col;
                break;
            }
        }

        //updates the board
        board.updateBoard(computerCell, move[0], move[1]);
    }
    else{
        cout << "Computer unable to make a move!" << "\n";
    }
}


//getters
bool Computer::ifNoMoves(){
    return moveList.empty();
}

const cellType Computer::getCellType(){
    return computerCell;
}