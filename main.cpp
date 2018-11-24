#include <iostream>
#include <random>

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
class Player{

private:
    vector<string>  guesses;
    vector<string> hits;

public:

    vector<string> getGuesses(){
        return guesses;
    }

    vector<string> getHits(){
        return hits;
    }

    string getGuess(int index){
        return guesses[index];
    }

    void addGuess(string guess){
        guesses.push_back(guess);
    }

    string getHit(int index){
        return hits[index];
    }

    void addHit(string guess){
        hits.push_back(guess);
    }

    bool checkForDuplicates(string input){
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


};

class Game {

private:

    int boardSize;
    int pieceNumber;
    string* setupStr;
    bool** humanBoard;
    bool** compBoard;

public:


    Game(int board, int pieces){
        boardSize = board;
        pieceNumber = pieces;
        setupStr = new string[pieceNumber];
        humanBoard = new bool*[boardSize+1];
        compBoard  = new bool*[boardSize+1];
        for(int i = 0; i < boardSize+1; ++i){
            humanBoard[i] = new bool[boardSize+1];
            compBoard[i] = new bool[boardSize+1];
        }

    }

    string* getSetupStr(){
        return setupStr;
    }

    bool** getHumanBoard(){
        return humanBoard;
    }

    bool** getCompBoard(){
        return compBoard;
    }

    string getSetupStrElement(int i){
        return setupStr[i];
    }

    void setSetupStrElement(int i, string val){
        setupStr[i] = val;
    }

    bool getBoardElement(bool** s, int row, int col) {
        return s[row][col];
    }

    void setBoardElement(bool** s, int row, int col, bool val) {
        s[row][col] = val;
    }

    int getBoardSize(){
        return boardSize;
    }

    void setBoardSize(int n){
        boardSize = n;
    }

    void setPieceNumber(int n){
        pieceNumber = n;
    }

    int getPieceNumber(){
        return pieceNumber;
    }

    string numerizeCoor(string s){
        s[0] = s[0]-16;
        return s;
    }

    string randomCoorPair(){
        mt19937 rng(rand());
        string s ="";
        uniform_int_distribution randNum(49,57-(9-boardSize));
        uniform_int_distribution randLet(65,73-(9-boardSize));
        s += randLet(rng);
        s += randNum(rng);
        return s;
    }

    int randomCoor(){
        mt19937 rng(rand());
        uniform_int_distribution randNum(1,boardSize);
        return randNum(rng);
    }

    void gameSetup(){
        for(int i = 0; i < boardSize; i++){
            for(int j = 0; j < boardSize; j++){
                humanBoard[i][j] = false;
                compBoard[i][j] = false;
            }
        }

        int x,y;
        for (int i = 0; i < pieceNumber; i++){
            setupStr[i] = numerizeCoor(setupStr[i]);
            x = setupStr[i][0] - '0';
            y = setupStr[i][1] - '0';
            setBoardElement(humanBoard, x, y, true);
        }

        for (int i = 0; i < pieceNumber; i++){
            x = randomCoor();
            y = randomCoor();
            while(compBoard[x][y]){
                x = randomCoor();
                y = randomCoor();
            }
            setBoardElement(compBoard, x, y, true);
        }
    }



    string fixCoorInput(string s) {
        string n="";
        if (s[0] > 96 && s[0] < 106) {
            n += (s[0] - 32);
            n += s[1];
            return n;
        }
        return s;
    }

    bool verifyCoorInput(string s) {
        if (s.length() != 2) {
            return false;
        } else if (s[1] > (57 - (9-boardSize)) || s[1] < 49 ) {
            return false;
        } else if (s[0] < 65 || (s[0] > (73 - (9-boardSize)) && s[0] < 96) || s[0] > (105 - (9-boardSize))) {
            return false;
        } else {
            return true;
        }
    }

    bool checkForDuplicates(string* s,string input){
        for(int i = 0; i < boardSize; i++){
            if (input == s[i]){
                return false;
            }
        }
        return true;
    }

    void printCoordinates(string* s){
        cout << "Your coordinates are" << endl << "{ ";
        for (int i = 0; i < pieceNumber; i++){
            cout << getSetupStrElement(i) << " ";
        }
        cout << "}" << endl;
    }

    void printGameBoard(Player human, Player comp) {
        for (int i = 0; i <= (boardSize-2); i++){
            cout << " ";
        }
        cout << "You";
        for (int i = 0; i <= (2 * boardSize)+2; i++){
            cout << " ";
        }
        cout << "AI" << endl;
        for (int col = 0; col < boardSize + 1; col++) {
            for(int row = 0; row < boardSize + 1 ; row++) {
                if (col == 0) {
                    if (row == 0) {
                        cout << "  ";
                    } else {
                        cout << row << " ";
                    }

                } else if (row == 0) {
                    char i = 64 + col;
                    cout << i << " ";
                } else if (humanBoard[col][row]) {
                    cout << "@ ";
                } else {
                    cout << checkCoor(comp, col, row);
                }

            }
            cout << " |  ";
            for(int row = 0; row < boardSize + 1; row++){
                if ( col == 0){
                    if (row == 0){
                        cout << "  ";
                    } else {
                        cout << row << " ";
                    }
                }else if(row == 0){
                    char i = 64 + col;
                    cout << i << " ";

                } else {
                    cout << checkCoor(human, col, row);
                }
            }
            cout << endl;
        }
    }

    string checkCoor(Player s, int col, int row){
        string result;
        for (int i = 0; i < s.getGuesses().size(); i++) {
            string x = s.getGuess(i);
            if (int(x[1] - '0') == row && int(x[0]- '0')== col) {
                result = "O ";
                return result;
            }
        }
        for (int i = 0; i < s.getHits().size(); i++) {
            string x = s.getHit(i);
            if (int(x[1] - '0') == row && int(x[0]- '0')== col) {
                result = "X ";
                return result;
            }
        }
        result = "- ";
        return result;
    }

    void gamePlay(){
        string input;
        Player human;
        Player comp;
        printGameBoard(human, comp);
        while(boardStatus(humanBoard) && boardStatus(compBoard)){
            cout << "Please guess a coordinate" << endl;
            cin >> input;
            while(!verifyCoorInput(input)){ //Loop to verify valid input
                cout << "Invalid coordinate, please try again" << endl;
                cin >> input;
                verifyCoorInput(input);
            }
            input = fixCoorInput(input);
            string alphinput = input;
            input = numerizeCoor(input);
            while(!human.checkForDuplicates(input)){
                cout << "Duplicate coordinate, please try again" << endl;
                cin >> input;
                while(!verifyCoorInput(input)){ //Loop to verify valid input
                    cout << "Invalid coordinate, please try again" << endl;
                    cin >> input;
                    verifyCoorInput(input);
                }
                input = fixCoorInput(input);
                alphinput = input;
                input = numerizeCoor(input);
            }
            if(checkGuess(compBoard, input)){
                cout << "You guessed " << alphinput << " and HIT" << endl;
                hit(compBoard, input);
                human.addHit(input);
                if (!boardStatus(compBoard)) {
                    cout << "Congratulations!! You win!!" << endl;
                    break;
                }
            }else{
                cout << "You guessed " << alphinput << " and MISSED" << endl;
                human.addGuess(input);
            }
            input = randomCoorPair();
            while(!comp.checkForDuplicates(numerizeCoor(input))) {
                input = randomCoorPair();
            }
            alphinput = input;
            input = numerizeCoor(input);
            if(checkGuess(humanBoard, input)){
                cout << "AI guessed " << alphinput << " and HIT" << endl;
                hit(humanBoard, input);
                comp.addHit(input);
                if (!boardStatus(humanBoard)){
                    cout << "Better luck next time, AI wins!" << endl;
                    break;
                }
            }else{
                cout << "AI guessed " << alphinput << " and MISSED" << endl;
                comp.addGuess(input);
            }
            printGameBoard(human, comp);
        }
    }

    bool checkGuess(bool** board, string guess){
        int x = guess[0] - '0';
        int y = guess[1] - '0';
        if(board[x][y]){
            return true;
        }
        return false;
    }

    void hit(bool** board, string coor){
        int x = coor[0] - '0';
        int y = coor[1] - '0';
        board[x][y] = false;
    }

    bool boardStatus(bool** board){
        for(int i = 0; i <= boardSize; i++){
            for(int j = 0; j <=boardSize; j++){
                if(board[i][j]){
                    return true; //still pieces
                }
            }
        }
        return false; // no pieces remaining
    }

};




Game gameStartup(){
    cout << "Welcome to command line Battleship!" << endl;
    cout << "How big would you like the game board to be?" << endl;
    int size;
    while(!(cin>>size)) {
        cin.clear();
        cin.ignore(999,'\n');
        cout<<"Invalid data type! Please try again" << endl;
    }
    while (size > 9 || size < 1){
        cout << "Game boards of that size are not currently supported, please try again" << endl;
        while(!(cin>>size)) {
            cin.clear();
            cin.ignore(999,'\n');
            cout<<"Invalid data type! Please try again" << endl;
        }
    }
    cout << "How many game pieces would you like to play with?" << endl;
    int pieceNum;
    while(!(cin>>pieceNum)) {
        cin.clear();
        cin.ignore(999,'\n');
        cout<<"Invalid data type! Please try again" << endl;
    }
    while (pieceNum > size*size || pieceNum < 1){
        cout << "Your board size does not support that many game pieces, please try again" << endl;
        while(!(cin>>pieceNum)) {
            cin.clear();
            cin.ignore(999,'\n');
            cout<<"Invalid data type! Please try again" << endl;
        }
    }
    Game game(size, pieceNum);
    cout << "Follow each coordinate with the return key" << endl;
    string input;
    for (int i = 0; i < game.getPieceNumber(); i++){
        cout << "Please enter a coordinate" << endl;
        cin >> input;
        while(!game.verifyCoorInput(input)){ //Loop to verify valid input
            cout << "Invalid coordinate, please try again" << endl;
            cin >> input;
            game.verifyCoorInput(input);
        }
        input = game.fixCoorInput(input);
        while(!game.checkForDuplicates(game.getSetupStr(), input)){
                cout << "Duplicate coordinate, please try again" << endl;
                cin >> input;
                while(!game.verifyCoorInput(input)){ //Loop to verify valid input
                    cout << "Invalid coordinate, please try again" << endl;
                    cin >> input;
                    game.verifyCoorInput(input);
                }
                input = game.fixCoorInput(input);
            }
        game.setSetupStrElement(i,input);
    }
    game.printCoordinates(game.getSetupStr());
    game.gameSetup();
    return game;
}

int main() {
    srand(time(NULL));
    Game game = gameStartup();
    game.gamePlay();
    return 0;

}