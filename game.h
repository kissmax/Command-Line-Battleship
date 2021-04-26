#ifndef GAME_H
#define GAME_H
#include "player.h"
#include <string>
using namespace std;

class Game {

    private:

        int boardSize;
        vector<int> pieces;
        int numPieces;
        string gameSize;
        string* setupStr;
        Player human;
        Player ai;

    public:

        Game();

        string getGameSize() {return gameSize;}
        
        int getNumPieces() {return numPieces;}
        
        int getPieceLength(int index) {return pieces[index];}

        int getBoardSize() {return boardSize;}

        void setBoardSize(int n) {boardSize = n;}

        void setPieceNumber(int n) {numPieces = n;}

        string getPieceDesc(int size);

        string numerizeCoor(string s);

        string randomCoorPair();

        int randomCoor();

        void gameSetup();

        vector<string> getCoorVector(string s);

        bool verifyCoorInput(string s);

        bool verifyCoorRange(string s, int pieceSize);

        void printGameBoard();

        string checkCoor(Player s, int col, int row);

        string getGuess(Player human);

        void gamePlay();
};
#endif