#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
using namespace std;

class Player{

    private:

        vector<vector<bool>> board;
        int remainingPieces;
        vector<string> guesses;
        vector<string> hits;

    public:

        Player();

        Player(int boardSize, int numPieces);
        
        int testVal;

        int getRemainingPieces() {return remainingPieces;}

        //This is probably bad, maybe return a copy, not sure if needed.
        vector<vector<bool>> getBoard() {return board;}

        bool getBoardElement(int row, int col) {return board[row][col];}

        void setBoardElement(int row, int col, bool val) {board[row][col] = val;}

        bool noDuplicates(vector<string> coorVec);

        vector<string> getGuesses() {return guesses;}

        vector<string> getHits() {return hits;}

        string getGuess(int index) {return guesses[index];}

        void addGuess(string guess) {guesses.push_back(guess);}

        bool checkGuess(string guess);

        //what does this do wtf
        string getHit(int index) {return hits[index];}

        void markHit(string coor);

        void addHit(string guess) {hits.push_back(guess);}

        bool checkForDuplicates(string input);
        
        bool boardStatus() {return remainingPieces > 0 ?  true : false;}
};

#endif