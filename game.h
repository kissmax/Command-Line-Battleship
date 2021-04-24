#ifndef GAME_H
#define GAME_H
#include "player.h"
#include <string>
using namespace std;

class Game {

private:

    int boardSize;
    int pieceNumber;
    string* setupStr;
    bool** humanBoard;
    bool** compBoard;

public:


    Game(int board, int pieces);

    string* getSetupStr() {return setupStr;}

    bool** getHumanBoard() {return humanBoard;}

    bool** getCompBoard() {return compBoard;}

    string getSetupStrElement(int i) {return setupStr[i];}

    void setSetupStrElement(int i, string val) {setupStr[i] = val;}

    bool getBoardElement(bool** s, int row, int col) {return s[row][col];}

    void setBoardElement(bool** s, int row, int col, bool val) {s[row][col] = val;}

    int getBoardSize() {return boardSize;}

    void setBoardSize(int n) {boardSize = n;}

    void setPieceNumber(int n) {pieceNumber = n;}

    int getPieceNumber() {return pieceNumber;}

    string numerizeCoor(string s);

    string randomCoorPair();

    int randomCoor();

    void gameSetup();

    string fixCoorInput(string s);

    bool verifyCoorInput(string s);

    bool verifyCoorRange(string s, int pieceSize);

    bool checkForDuplicates(string* s,string input);

    void printCoordinates(string* s);

    void printGameBoard(Player human, Player comp);

    string checkCoor(Player s, int col, int row);

    string getGuess(Player human);

    void gamePlay();

    bool checkGuess(bool** board, string guess);

    void hit(bool** board, string coor);

    bool boardStatus(bool** board);

};

Game gameStartup();
#endif