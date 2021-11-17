#include "Board.hpp"
#include <iostream>
#include <cmath>
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
    for(int i = 0; i < numRows; i++)
        delete[] panel[i];
    delete[] panel;
}

void Board::print() const{
    for(int i = 0; i < 2 * numRows + 1; i++){
        if(i % 2){
            for(int j = 0; j < numCols; j++){
                int n = panel[i/2][j];
                if(n){
                    int digits = floor(log(n) / log(10)) + 1;
                    switch (digits) {
                        case 1:
                            cout << "|   " << n;
                            break;
                        case 2:
                            cout << "|  " << n;
                            break;
                        case 3:
                            cout << "| " << n;
                            break;
                        case 4:
                            cout << "|" << n;
                            break;
                    }
                }else
                    cout << "|    ";
            }
            cout << "|\n";
        }else{
            for(int j = 0; j < numCols; j++) {
                cout << "+----";
            }
            cout << "+\n";
        }
    }
}


