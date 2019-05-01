

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : John Ordoyo
// St.# : 301373568
// Email: john_ordoyo@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////


#include "Board.h"
#include "Players.h"
#include "Board.cpp"
#include "Players.cpp"
#include <iostream>
#include <vector>

using namespace std;

//displays the end of the game
void displayGameEnd( Board& board,  Player& player1,  Player& player2){
    board.displayBoard();
    if(board.getScore(player1.getCellType()) > board.getScore(player2.getCellType())){
        cout << "Player 1 wins!" << "\n";
    }
    else if(board.getScore(player1.getCellType()) < board.getScore(player2.getCellType())){
        cout << "Player 2 wins!" << "\n";
    }
    else{
        cout << "Draw!" << "\n";
    }
}


//asks the user if it wants to play again
void ifPlayAgain( Board& board, bool& playing){

    string input;
    cout << "Would you like to play again? (type yes or Yes to keep playing, anything else if you don't want to play): ";
    getline(cin, input);


    //if user said yes
    if(input == "Yes" || input == "yes"){
        board.resetBoard(board.getRow(), board.getCol());
        playing = true;
    }
    //if the user said anything else
    else{
        playing = false;
    }

}


//returns true if either players can not make a move or if the board is full
bool ifGameEnd( Board& board,  Player& player1,  Player& player2){
    return((player1.ifNoMoves() && player2.ifNoMoves()) || board.ifBoardFull());
}

void playReversi(Board& board, Player& player1, Player& player2){

    //plays the game based off a while loop that checks a boolean.
    //If boolean is true, play the game, else ask the user if they want to
    //play the game.

    bool playing = true;
    while(playing){
        cout << "PLAYER 1 TURN" << "\n";
        cout << "-------------" << "\n";
        player1.determineMove(board);
        cout << "PLAYER 2 TURN" << "\n";
        cout << "-------------" << "\n";
        player2.determineMove(board);

        if(ifGameEnd(board, player1, player2)){
            displayGameEnd(board, player1, player2);
            ifPlayAgain(board, playing);
        }
    }

}



int main(){
    
    Board board{8, 8};
    User firstPlayer{player1};
    Computer secondPlayer{player2};
    
    playReversi(board, firstPlayer, secondPlayer);
}