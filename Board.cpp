#include "Board.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
using std::cout;
using std::vector;

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
            panel[i][j] = i* 3 + 2 * j;
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
            for(int j = 0; j < numCols; j++)
                cout << "+----";
            cout << "+\n";
        }
    }
}

bool Board::noAdjacentSameValue() const{
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            if(!panel[i][j])
                return false;
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j) {
            if (i - 1 >= 0) {
                if (panel[i][j] == panel[i - 1][j])
                    return false;
            }
            if (i + 1 < numRows) {
                if (panel[i][j] == panel[i + 1][j])
                    return false;
            }
            if (j - 1 >= 0) {
                if (panel[i][j] == panel[i][j - 1])
                    return false;
            }
            if (j + 1 < numCols) {
                if (panel[i][j] == panel[i][j + 1])
                    return false;
            }
        }
    return true;
}

void Board::selectRandomCell(int& row, int& col){
    int zeroes = 0;
    vector<int> cells;
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j){
            if(!panel[i][j]){
                cells.push_back(i * numCols + j);
                zeroes++;
            }
        }
    if(!zeroes and this->noAdjacentSameValue()){
        cout << "Game over. Try again.\n";
    }else{
        if(zeroes){
            srand(1);
            int n = cells[rand() % cells.size()];
            row = n / numCols;
            col = n % numCols;
            panel[row][col] = 1;
            this->print();
            if(!--zeroes and this->noAdjacentSameValue())
                cout << "Game over. Try again.\n";
        }
    }
}



