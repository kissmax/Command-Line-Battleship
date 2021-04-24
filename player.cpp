#include "player.h"

using namespace std;

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