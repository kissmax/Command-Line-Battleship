#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
using namespace std;

class Player{

    private:
        vector<string>  guesses;
        vector<string> hits;

    public:

        vector<string> getGuesses() {return guesses;}

        vector<string> getHits() {return hits;}

        string getGuess(int index) {return guesses[index];}

        void addGuess(string guess) {guesses.push_back(guess);}

        string getHit(int index) {return hits[index];}

        void addHit(string guess) {hits.push_back(guess);}

        bool checkForDuplicates(string input);
};

#endif