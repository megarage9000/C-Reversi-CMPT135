
#include <iostream>
#include "Board.h"

#ifndef Players_H
#define Players_H

using namespace std;

//abstract Player Class
class Player {
       
    public:
        virtual void determineMove(Board& board) = 0;
        virtual bool ifNoMoves() = 0;
        virtual const cellType getCellType() = 0;
        virtual ~Player();
        
};


//children classes of Player: User and Computer
class User : public Player {

    private:
        int move[2];
        vector<Cell> moveList;
        cellType playerCell;

    public:

        User(cellType c);
        void determineMove(Board& board); 

        //filters input;
        bool ifValidInput(string& input,Board& board);  

        //getters
        bool ifNoMoves();
        const cellType getCellType();
       
        
};

class Computer: public Player {

    private:
        int move[2];
        vector<Cell> moveList;
        cellType computerCell;
    public:
        Computer(cellType c);
        void determineMove(Board& board);

        //getters
        bool ifNoMoves();
        const cellType getCellType();
};

//helper function for the User class

void toLower(string& str){
    for(int i = 0; i < str.size(); i++){
        str[i] = tolower(str[i]);
    }
}

#endif