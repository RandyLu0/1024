#include "Board.hpp"
#include <iostream>
using std::cout;

Board::Board() {
    max = 0;
    target = 32;
    numCols = 3;
    numRows = 3;
    allocateMemory();
}

Board::Board(int m) {
    max = 0;
    target = 32;
    numRows = m >= 1 ? m : 3;
    numCols = m >= 1 ? m : 3;
    allocateMemory();
}

Board::Board(int m, int n) {
    max = 0;
    target = 32;
    numRows = m >= 1 and n >= 1 ? m : 3;
    numCols = m >= 1 and n >= 1 ? n : 3;
    allocateMemory();
}

void Board::allocateMemory() {
    panel = new int* [numRows];
    for (int i = 0; i < numRows; ++i)
        panel[i] = new int[numCols];

    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            panel[i][j] = 0;
}

Board::~Board() {
    for(int i = 0; i < numRows; i++){
        delete[] panel[i];
    }
    delete[] panel;
}

void Board::print() const{
    for(int i = 0; i < 2 * numRows + 1; i++){
        if(i % 2){
            for(int j = 0; j < numCols; j++){
                cout << "|   ";
                if(panel[i/2][j])
                    cout << panel[i][j];
                else{
                    cout << " ";
                }
            }
            cout << "|\n";
        }else{
            for(int j = 0; j < numCols; j++)
                cout << "+----";
            cout << "+\n";
        }
    }
}