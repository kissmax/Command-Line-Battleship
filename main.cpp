#include <iostream>
#include <random>
#include <string>
#include "time.h"
#include "game.h"
#include "player.h"

using namespace std;

/*class GamePiece {  Place holder for future iterations where pieces have size and placement attributes

private:

    int size;

public:

    int getSize(){
        return size;
    }
    void setSize(int n){
        size = n;
    }

};
*/

int main() {
    srand(time(NULL));
    Game game = gameStartup();
    game.gamePlay();
    return 0;

}
