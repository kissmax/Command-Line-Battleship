#include "game.h"
#include "player.h"
#include <iostream>
#include <random>
using namespace std;

Game :: Game(int board, int pieces){
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


string Game :: numerizeCoor(string s){
    s[0] = s[0]-16;
    return s;
}

string Game :: randomCoorPair(){
    mt19937 rng(rand());
    string s ="";
    uniform_int_distribution<int> randNum(49,57-(9-boardSize));
    uniform_int_distribution<int> randLet(65,73-(9-boardSize));
    s += randLet(rng);
    s += randNum(rng);
    return s;
}

int Game :: randomCoor(){
    mt19937 rng(rand());
    uniform_int_distribution<int> randNum(1,boardSize);
    return randNum(rng);
}

void Game :: gameSetup(){
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

string Game :: fixCoorInput(string s) {
    string n="";
    if (s[0] > 96 && s[0] < 106) {
        n += (s[0] - 32);
        n += s[1];
        return n;
    }
    return s;
}

bool Game :: verifyCoorInput(string s) {
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

bool Game :: verifyCoorRange(string s, int pieceSize) {
    string coor1 = s.substr(0,s.find('-'));
    string coor2 = s.substr(s.find('-')+1,s.length()-1);
    if (!verifyCoorInput(coor1) || !verifyCoorInput(coor2))
        return false;
    if ((coor1[0] != coor2[0]) && (coor1[1] != coor2[1]))
        return false;
    if (coor1[1] == coor2[1]){;
        if ((pieceSize - (int(coor2[0]) - int(coor1[0]))) != 1)
        return false;
    }
    else if (coor1[0] == coor2[0]){
        if (pieceSize - (coor2[1] - coor1[1]) != 1)
        return false;
    }
    return true;
}

bool Game :: checkForDuplicates(string* s,string input){
    for(int i = 0; i < boardSize; i++){
        if (input == s[i]){
            return false;
        }
    }
    return true;
}

void Game :: printCoordinates(string* s){
    cout << "Your coordinates are" << endl << "{ ";
    for (int i = 0; i < pieceNumber; i++){
        cout << getSetupStrElement(i) << " ";
    }
    cout << "}" << endl;
}

void Game :: printGameBoard(Player human, Player comp) {
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

string Game :: checkCoor(Player s, int col, int row){
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

string Game :: getGuess(Player human){
    string input;
    cout << "Please guess a coordinate" << endl;
    cin >> input;
    while(!verifyCoorInput(input)){ //Loop to verify valid input
        cout << "Invalid coordinate, please try again" << endl;
        cin >> input;
        verifyCoorInput(input);
    }
    input = fixCoorInput(input);
    while(!human.checkForDuplicates(numerizeCoor(input))){
        cout << "Duplicate coordinate, please try again" << endl;
        cin >> input;
        while(!verifyCoorInput(input)){ //Loop to verify valid input
            cout << "Invalid coordinate, please try again" << endl;
            cin >> input;
        }
        input = fixCoorInput(input);
    }
    input = fixCoorInput(input);
    return input;
}

void Game :: gamePlay(){
    string input;
    string alphinput;
    Player human;
    Player comp;
    printGameBoard(human, comp);
    while(boardStatus(humanBoard) && boardStatus(compBoard)){
        input = getGuess(human);
        alphinput = input;
        input = numerizeCoor(input);
        while(checkGuess(compBoard,input)){
            cout << "You guessed " << alphinput << " and HIT" << endl;
            hit(compBoard, input);
            human.addHit(input);
            printGameBoard(human, comp);
            if (!boardStatus(compBoard)) {
            cout << "Congratulations!! You win!!" << endl;
            return;
            }
            input = getGuess(human);
            alphinput = input;
            input = numerizeCoor(input);
        }
        if(!checkGuess(compBoard,input)){
            cout << "You guessed " << alphinput << " and MISSED" << endl;
            human.addGuess(input);
        }
        input = randomCoorPair();
        while(!comp.checkForDuplicates(numerizeCoor(input))) {
            input = randomCoorPair();
        }
        while(checkGuess(humanBoard, numerizeCoor(input))){
            alphinput = input;
            input = numerizeCoor(input);
            cout << "AI guessed " << alphinput << " and HIT" << endl;
            hit(humanBoard, input);
            comp.addHit(input);
            printGameBoard(human, comp);
            if (!boardStatus(humanBoard)){
            cout << "Better luck next time, AI wins!" << endl;
            return;
            }
            input = randomCoorPair();
            while(!comp.checkForDuplicates(numerizeCoor(input))) {
                input = randomCoorPair();
            }
        }
        if (!checkGuess(humanBoard, numerizeCoor(input))){
            cout << "AI guessed " << input << " and MISSED" << endl;
            comp.addGuess(numerizeCoor(input));
        }
        printGameBoard(human, comp);
    }
}

bool Game :: checkGuess(bool** board, string guess){
    int x = guess[0] - '0';
    int y = guess[1] - '0';
    if(board[x][y]){
        return true;
    }
    return false;
}

void Game :: hit(bool** board, string coor){
    int x = coor[0] - '0';
    int y = coor[1] - '0';
    board[x][y] = false;
}

bool Game :: boardStatus(bool** board){
    for(int i = 0; i <= boardSize; i++){
        for(int j = 0; j <=boardSize; j++){
            if(board[i][j]){
                return true; //still pieces
            }
        }
    }
    return false; // no pieces remaining
}

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
    cout << "Now place your pieces by entering coordinate ranges (ex. a3-a5)" << endl;
    cout << "Follow each coordinate with the return key" << endl;
    string input;
    for (int i = 0; i < game.getPieceNumber(); i++){
        cout << "Please enter a coordinate for a 3 space piece" << endl;
        cin >> input;
        while(!game.verifyCoorRange(input,3)){ //Loop to verify valid input
            cout << "Invalid coordinate range, please try again" << endl;
            cin >> input;
            //game.verifyCoorInput(input);
        }
        //cout << "i did it" << endl;
        //Need to implent duplicate coordinates for placing ships
        //Also display board after placing each ship
        //Also probably less customizability, just make small medium large game mode
        //Comment this shitshow
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