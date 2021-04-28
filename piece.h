#ifndef PIECE_H
#define PIECE_H
#include <string>
using namespace std;

class Piece {

    private:
        bool isAlive;
        int size;
        int hits;
        bool isHorizontal;
        pair<int,int> front;

    public:

        Piece();
};
#endif