//
//  Minesweeper.cpp
//  Minesweeper
//
//  Created by Samuel Zaldivar on 8/24/18.
//  Copyright © 2018 Samuel Zaldivar. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <string>
using namespace std;


class Box{
public:
    string displayElement = "[]";
    string element;
    bool opened = false;
    
    Box(){
        element = "0";
    }
    void incrementElement();
};

void Box::incrementElement(){
    
    int code = static_cast<int>(element[0]);
    code++;
    element = static_cast<char>(code);
}

class Game{
private:
    
    Box gameBoard[9][9] = {};
    void makeBoard();
    int getRandomNum(long);
    void incremntAroundMine(int, int);
    void zeroDisplay(int, int);
    
public:
    Game();
    void showBoard();
    void showElementBoard();
    bool selectElement(int,int);
};

Game::Game(){
    makeBoard();
    showElementBoard();
    showBoard();
}

void Game::makeBoard(){
    
    long i = 100;
    
    for(int mineNum = 1; mineNum <= 10; mineNum++){
    
        time_t seconds;
        seconds = time (NULL);
        
        int rowNum = getRandomNum(mineNum + i);
        i = --i * seconds;
        int colNum = getRandomNum(mineNum + rowNum + i);
        i = --i * seconds;
        
        gameBoard[rowNum][colNum].element = "*";
        incremntAroundMine(rowNum, colNum);
    }
}

void Game::incremntAroundMine(int mineRow, int mineCol){
    
    int upperRow, lowerRow, leftCol, rightCol;
    
    if(mineRow == 0){
        lowerRow = 0;
        upperRow = mineRow + 1;
    }
    else if(mineRow == 8){
        lowerRow = mineRow - 1;
        upperRow = 8;
    }
    else{
        lowerRow = mineRow - 1;
        upperRow = mineRow + 1;
    }
    
    if(mineCol == 0){
        leftCol = 0;
        rightCol = mineCol + 1;
    }
    else if(mineCol == 8){
        leftCol = mineCol - 1;
        rightCol = 8;
    }
    else{
        leftCol = mineCol - 1;
        rightCol = mineCol + 1;
    }
    
    for(int row = lowerRow; row <= upperRow; row++){
        for(int col = leftCol; col <= rightCol; col++){
            if(gameBoard[row][col].element != "*"){
                gameBoard[row][col].incrementElement();
            }
        }
    }
}

int Game::getRandomNum(long i){
    
    time_t seconds;
    seconds = time (NULL) + i;
    
    unsigned int seed = static_cast<unsigned int>(seconds);
    srand(seed);
    
    int randomNum = (rand() % (8 - 0 + 1)) + 0;
    
    return randomNum;
}

bool Game::selectElement(int row, int col){
    
    bool returnValue;
    
    gameBoard[row][col].displayElement = gameBoard[row][col].element;
    gameBoard[row][col].opened = true;
    
    if(gameBoard[row][col].element == "*"){
        returnValue =  false;
    }
    else{
        
        if(gameBoard[row][col].element == "0"){
            zeroDisplay(row, col);
        }
        
        returnValue =  true;
    }
    
    showElementBoard();
    showBoard();
    return returnValue;
}

void Game::zeroDisplay(int row, int col){
    
    int upperRow, lowerRow, leftCol, rightCol;
    
    if(row == 0){
        lowerRow = 0;
        upperRow = row + 1;
    }
    else if(row == 8){
        lowerRow = row - 1;
        upperRow = 8;
    }
    else{
        lowerRow = row - 1;
        upperRow = row + 1;
    }
    
    if(col == 0){
        leftCol = 0;
        rightCol = col + 1;
    }
    else if(col == 8){
        leftCol = col - 1;
        rightCol = 8;
    }
    else{
        leftCol = col - 1;
        rightCol = col + 1;
    }
    
    for(int r = lowerRow; r <= upperRow; r++){
        for(int c = leftCol; c <= rightCol; c++){
            
            if(gameBoard[r][c].opened != true){
                gameBoard[r][c].displayElement = gameBoard[r][c].element;
                gameBoard[r][c].opened = true;
                
                if(gameBoard[r][c].element == "0"){
                    zeroDisplay(r, c);
                }
            }
        }
    }
}

void Game::showBoard(){
    cout << endl;
    cout << "  0 1 2 3 4 5 6 7 8" << endl;
    for(int row = 0; row < 9; row++){
        cout << row;
        for(int col = 0; col < 9; col++){
            cout << setw(2) << gameBoard[row][col].displayElement <<  "";
        }
        cout << endl;
    }
}

void Game::showElementBoard(){
    cout << endl;
    cout << "  0 1 2 3 4 5 6 7 8" << endl;
    for(int row = 0; row < 9; row++){
        cout << row;
        for(int col = 0; col < 9; col++){
            cout << setw(2) << gameBoard[row][col].element <<  "";
        }
        cout << endl;
    }
}














void selectNewSquare(int*, int*);

int main(){
    
    cout << "Let's play Minesweeper!!" << endl << endl;
    Game g;
    
    bool gameOver = false;
    
    int row, col;
    
    while (!gameOver) {
        selectNewSquare(&row, &col);
        
        if(!g.selectElement(row, col)){
            cout << "Game Over!" << endl;
            gameOver = true;
        }
    }
}

void selectNewSquare(int *row, int *col){
    cout << endl << "Enter your square: " << endl;
    
    cout << "Row: ";
    cin >> *row;
    
    cout << "Col: ";
    cin >> *col;
}

