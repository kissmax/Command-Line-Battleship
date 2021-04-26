#include "game.h"
#include "player.h"
#include <iostream>
#include <random>
using namespace std;

Game :: Game(){
    cout << "Welcome to command line Battleship!" << endl;
    cout << "What size game would you like to play?" << endl;
    cout << "1. Small (5x5)\n2. Medium (8x8)\n3. Large (10x10)" << endl;
    int sizeInput;
    cin >> sizeInput;
    while (sizeInput > 3 || sizeInput < 1 || !cin.good()){
        cin.clear();
        cin.ignore(999,'\n');
        cout << "Invalid response! Please select option 1, 2, or 3." << endl;
        cin >> sizeInput;
    }
    switch (sizeInput){
        case 1:
            boardSize = 5;
            gameSize = "Small";
            pieces = {2,2,4};
            break;
        case 2:
            boardSize = 8;
            gameSize = "Medium";
            pieces = {2,2,2,3,3,4,5};
            break;
        case 3:
            boardSize = 10;
            gameSize = "Large";
            pieces = {2,2,2,2,3,3,3,4,4,6};
            break;
    }
    numPieces = pieces.size();
    Player human(boardSize, numPieces);
    Player ai(boardSize, numPieces);
    printGameBoard();
    cout << "Now place your " << numPieces << " pieces by entering coordinate ranges (ex. a3-a5)" << endl;
    cout << "Follow each coordinate range with the return key" << endl;
    string input;
    int pieceLen;
    for (int i = 0; i < numPieces; i++){
        pieceLen = getPieceLength(i);
        cout << "Please enter a coordinate for a " << getPieceDesc(pieceLen) << " which occupies " << pieceLen << " spaces." << endl;
        cin >> input;
        while(!verifyCoorRange(input, pieceLen)){ //Loop to verify valid input
            cout << "Invalid coordinate range, please try again" << endl;
            cin >> input;
        }
        vector<string> coorVec = getCoorVector(input);
        vector<string>::iterator it;
        for (it = coorVec.begin(); it != coorVec.end(); it++)
        {
            string coorPair = *it;
            int row = coorPair[0] - 65;
            int col = coorPair[1] - '0';
            human.setBoardElement(col,row,true);
        }
        printGameBoard();

        //Need to implent duplicate coordinates for placing ships
        //Also display board after placing each ship
        //Comment this shitshow
        /*
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
            */
        //game.setSetupStrElement(i,input);
    }
    //game.printCoordinates(game.getSetupStr());
    //game.gameSetup();
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
            human.getBoard()[i][j] = false;
            ai.getBoard()[i][j] = false;
        }
    }

    int x,y;
    for (int i = 0; i < numPieces; i++){
        setupStr[i] = numerizeCoor(setupStr[i]);
        x = setupStr[i][0] - '0';
        y = setupStr[i][1] - '0';
        human.setBoardElement(x, y, true);
    }

    for (int i = 0; i < numPieces; i++){
        x = randomCoor();
        y = randomCoor();
        while(ai.getBoardElement(x, y)){
            x = randomCoor();
            y = randomCoor();
        }
        ai.setBoardElement(x, y, true);
    }
}

string Game :: getPieceDesc(int size){
    switch (size){
        case 2:
            return "patrol boat";
            break;
        case 3:
        {
            int choice = rand() % 2;
            if (choice == 0){
                return "submarine";
            }
            else {
                return "destroyer";
            }
            break;
        }
        case 4:
            return "battleship";
            break;
        case 5:
            return "carrier";
            break;
    }
    return "";
}

vector<string> Game :: getCoorVector(string s) {
    vector<string> coorVec;
    string coor1 = s.substr(0,s.find('-'));
    string coor2 = s.substr(s.find('-')+1,s.length()-1);
    char row1 = toupper(coor1[0]);
    int col1 = coor1[1] - '0';
    char row2 = toupper(coor2[0]);
    int col2 =  coor2[1] - '0';
    //if the rows are the same, loop through the columns and add values to vector
    if (row1 == row2){
        for (int i = col1; i <= col2; ++i){
            coorVec.push_back(row1+to_string(i));
        }
    }
    //if the columns are the same, loop through the rows and add values to vector
    else{
        for(char i = row1; i <= row2; ++i){
            coorVec.push_back(i+to_string(col1));
        }
    }
    return coorVec;
}

bool Game :: verifyCoorInput(string s) {
    if (s.length() != 2) {
        cout << "Verify err1" << endl;
        return false;
    }
    char row = tolower(s[0]);
    int col = s[1] - '0';
    //check if row is between A and the "boardSize"th letter of the alphabet
    //checks if char is less than ascii 'a' which is 97
    //or if char is greater than the ascii value of 96 + boardsize, which is the last letter on the grid
    if (row < 97 || row > 96 + boardSize) {
        cout << "Verify err2" << endl;
        return false;
    }
    //check if col is between 0 and boardSize
    if (col < 0 || col > boardSize) {
        cout << "Verify err3" << endl;
        return false;
    } else {
        return true;
    }
}

bool Game :: verifyCoorRange(string s, int pieceSize) {
    string coor1 = s.substr(0,s.find('-'));
    string coor2 = s.substr(s.find('-')+1,s.length()-1);
    int row1 = coor1[0];
    int col1 = coor1[1];
    int row2 = coor2[0];
    int col2 = coor2[1];
    //assure the individual coordinate values are not the same
    if ((row1 != row2) && (col1 != col2)){
        cout << "Range err1" << endl;
        return false;
    }
    //assure the individual coordinate values exist on the board
    if (!verifyCoorInput(coor1) || !verifyCoorInput(coor2)){
        cout << "Range err2" << endl;
        return false;
    }
    //if the coordinates fall in the same column make sure it occupies pieceSize spaces
    if (col1 == col2){
        if (row2 - row1 != pieceSize-1){
            cout << "row2-row1: " << row2-row1 << endl;
            cout << "Range err3" << endl;
            return false;
        }
    }
    //if the coordinates fall in the same row make sure it occupies pieceSize spaces
    else if (row1 == row2){
        if (col2 - col1 != pieceSize-1){
            cout << "col2-col1: " << col2-col1 << endl;
            cout << "Range err4" << endl;
            return false;
        }
    }
    vector<string> coorVec = getCoorVector(s);
    if (!human.noDuplicates(coorVec)){
        cout << "Range err5" << endl;
        return false;
    }
    return true;
}

void Game :: printGameBoard() {
    for (int i = 0; i <= (boardSize-1); ++i){
        cout << " ";
    }
    cout << "You";
    for (int i = 0; i <= (2 * boardSize)+2; ++i){
        cout << " ";
    }
    cout << "AI" << endl;
    for (int col = 0; col < boardSize + 1; col++) {
        for(int row = 0; row < boardSize + 1; row++) {
            if (col == 0) {
                if (row == 0) {
                    cout << "  ";
                }
                if (row < boardSize){
                    cout << row << " ";
                }
            } else if (row == 0) {
                char i = 64 + col;
                cout << i << " ";
            } else if (human.getBoardElement(col-1, row)) {
                cout << "@ ";
            } else {
                cout << checkCoor(ai, col-1, row);
            }
        }
        cout << " |  ";
        for(int row = 0; row < boardSize + 1; row++){
            if ( col == 0){
                if (row == 0){
                    cout << "  ";
                }
                if (row < boardSize){
                    cout << row << " ";
                }
            }else if(row == 0){
                char i = 64 + col;
                cout << i << " ";

            } else {
                cout << checkCoor(human, col-1, row);
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
    while(!human.checkForDuplicates(numerizeCoor(input))){
        cout << "Duplicate coordinate, please try again" << endl;
        cin >> input;
        while(!verifyCoorInput(input)){ //Loop to verify valid input
            cout << "Invalid coordinate, please try again" << endl;
            cin >> input;
        }
    }
    return input;
}

void Game :: gamePlay(){
    string input;
    string alphinput;
    printGameBoard();
    while(human.boardStatus() && ai.boardStatus()){
        input = getGuess(human);
        alphinput = input;
        input = numerizeCoor(input);
        while(ai.checkGuess(input)){
            cout << "You guessed " << alphinput << " and HIT" << endl;
            ai.markHit(input);
            human.addHit(input);
            printGameBoard();
            if (!ai.boardStatus()) {
            cout << "Congratulations!! You win!!" << endl;
            return;
            }
            input = getGuess(human);
            alphinput = input;
            input = numerizeCoor(input);
        }
        if(!ai.checkGuess(input)){
            cout << "You guessed " << alphinput << " and MISSED" << endl;
            human.addGuess(input);
        }
        input = randomCoorPair();
        while(!ai.checkForDuplicates(numerizeCoor(input))) {
            input = randomCoorPair();
        }
        while(human.checkGuess( numerizeCoor(input))){
            alphinput = input;
            input = numerizeCoor(input);
            cout << "AI guessed " << alphinput << " and HIT" << endl;
            human.markHit(input);
            ai.addHit(input);
            printGameBoard();
            if (!human.boardStatus()){
            cout << "Better luck next time, AI wins!" << endl;
            return;
            }
            input = randomCoorPair();
            while(!ai.checkForDuplicates(numerizeCoor(input))) {
                input = randomCoorPair();
            }
        }
        if (!human.checkGuess(numerizeCoor(input))){
            cout << "AI guessed " << input << " and MISSED" << endl;
            ai.addGuess(numerizeCoor(input));
        }
        printGameBoard();
    }
}