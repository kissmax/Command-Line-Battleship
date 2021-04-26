#include "player.h"
#include <iostream>
using namespace std;

Player :: Player() {
    vector<bool> col(10);
    for (int i = 0; i < 10; ++i){
        board.push_back(col);
    }
    remainingPieces = 10;
}

Player :: Player(int boardSize, int numPieces){
    vector<bool> col(boardSize);
    for (int i = 0; i < boardSize; ++i){
        board.push_back(col);
    }
    remainingPieces = numPieces;
}

bool Player :: checkGuess(string guess){
    int x = guess[0] - '0';
    int y = guess[1] - '0';
    if(board[x][y]){
        return true;
    }
    return false;
}

void Player :: markHit(string coor){
    int x = coor[0] - '0';
    int y = coor[1] - '0';
    board[x][y] = false;
}

bool Player :: noDuplicates(vector<string> coorVec){
    vector<string>::iterator it;
    for (it = coorVec.begin(); it != coorVec.end(); it++)
    {
        string coorPair = *it;
        int row = coorPair[0] - 65;
        int col = coorPair[1] - '0';
        if (board[col][row])
            return false;
    }
    return true;
}

bool Player :: checkForDuplicates(string input){
    for(int i = 0; i < guesses.size(); i++){
        if(guesses[i] == input){
            return false;
        }
    }
    for(int i = 0; i < hits.size(); i++){
        if (hits[i] == input){
            return false;
        }
    }
    return true;
}