#include "Board.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iomanip>
using std::cout;
using std::vector;
using std::setw;

Board::Board() {
    max = 0; target = 32;
    numCols = 3; numRows = 3;
    allocateMemory();
}

Board::Board(int m) {
    max = 0; target = 32;
    numRows = m >= 1 ? m : 3;
    numCols = m >= 1 ? m : 3;
    allocateMemory();
}

Board::Board(int m, int n) {
    max = 0; target = 32;
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

int Board::find_max() const {
    int m;
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            if(panel[i][j] > m) m = panel[i][j];
    return m;
}

void Board::print() const{
    for(int i = 0; i < 2 * numRows + 1; i++){
        if(i % 2){
            for(int j = 0; j < numCols; j++){
                int n = panel[i/2][j];
                if(n > 0){
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
                }else {
                    cout << "|    ";
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

void Board::pressUp(){
    vector<int> col;
    vector<int> col2;
    int r,r1;
    for(int j = 0; j < numCols; j++){
        r = 0;
        r1 = 0;
        int diff = j * numRows;
        for (int i = 0; i < numRows; ++i)
            if (panel[i][j]){
                col.push_back(panel[i][j]);
                r++;
            }
        for (int i = r; i < numRows; ++i)
            col.push_back(0);
        for (int i = 0; i < numRows - 1; ++i)
            if(col[diff + i] == col[diff+i+1]){
                col[diff + i] *= 2;
                col[diff+i+1] = 0;
            }
        for (int i = 0; i < numRows; ++i)
            if(col[diff+i]){
                r1++;
                col2.push_back(col[diff+i]);
            }
        for (int i = r1; i < numRows; ++i)
            col2.push_back(0);
        for (int i = 0; i < numRows; ++i)
                panel[i][j] = col2[diff+i];
    }
    this->selectRandomCell(r,r1);
}

void Board::pressDown(){
    vector<int> col;
    vector<int> col2;
    int r,r1;
    for(int j = 0; j < numCols; j++){
        r = 0;
        r1 = 0;
        int diff = j * numRows;
        for (int i = numRows - 1; i >= 0; --i)
            if (panel[i][j]){
                col.push_back(panel[i][j]);
                r++;
            }
        for (int i = r; i < numRows; ++i)
            col.push_back(0);
        for (int i = 0; i < numRows - 1; ++i)
            if(col[diff + i] == col[diff+i+1]){
                col[diff + i] *= 2;
                col[diff+1 + i] = 0;
            }
        for (int i = 0; i < numRows; ++i)
            if(col[diff + i]){
                r1++;
                col2.push_back(col[diff + i]);
            }
        for (int i = r1; i < numRows; ++i)
            col2.push_back(0);
        for (int i = 0; i < numRows; ++i)
            panel[i][j] = col2[(diff + numRows - 1) - i];
    }
    this->selectRandomCell(r,r1);
}

void Board::pressLeft(){
    vector<int> row;
    vector<int> row2;
    int c,c1;
    for (int i = 0; i < numRows; ++i) {
        c = 0;
        c1 = 0;
        int diff = i * numCols;
        for (int j = 0; j < numCols; ++j) {
            if(panel[i][j]){
                row.push_back(panel[i][j]);
                c++;
            }
        }
        for (int j = c; j < numCols; ++j) {
            row.push_back(0);
        }
        for (int j = 0; j < numCols - 1; ++j) {
            if(row[diff + j] == row[diff +j+1]){
                row[diff + j] *= 2;
                row[diff+j+1] = 0;
            }
        }
        for (int j = 0; j < numCols; ++j) {
            if(row[diff+j]){
                c1++;
                row2.push_back(row[diff+j]);
            }
        }
        for (int j = c1; j < numCols; ++j) {
            row2.push_back(0);
        }
        for (int j = 0; j < numCols; ++j) {
            panel[i][j] = row2[diff+j];
        }
    }
    this->selectRandomCell(c,c1);
}

void Board::pressRight(){
    vector<int> row;
    vector<int> row2;
    int c,c1;
    for (int i = 0; i < numRows; ++i) {
        c = 0;
        c1 = 0;
        int diff = i * numCols;
        for (int j = numCols - 1; j >= 0; --j) {
            if(panel[i][j]){
                row.push_back(panel[i][j]);
                c++;
            }
        }
        for (int j = c; j < numCols; ++j) {
            row.push_back(0);
        }
        for (int j = 0; j < numCols - 1; ++j) {
            if(row[diff + j] == row[diff +j+1]){
                row[diff + j] *= 2;
                row[diff+j+1] = 0;
            }
        }
        for (int j = 0; j < numCols; ++j) {
            if(row[diff+j]){
                c1++;
                row2.push_back(row[diff+j]);
            }
        }
        for (int j = c1; j < numCols; ++j) {
            row2.push_back(0);
        }
        for (int j = 0; j < numCols; ++j) {
            panel[i][j] = row2[diff+numCols - 1-j];
        }
    }
    this->selectRandomCell(c,c1);
}

void Board::start(){
    int round = 1, a,b; selectRandomCell(a,b);
    while (true){
        if (max == target){
            cout << "Congragulations!";
            break;
        }
        if (getchar() == '\033') {
            getchar();
            switch(getchar()) {
                case 'A':
                    cout << "Round " << setw(4) << round << ": Pressed UP. \n";
                    pressUp(); round++; break;
                case 'B':
                    cout << "Round " << setw(4) << round << ": Pressed DOWN. \n";
                    pressDown(); round++; break;
                case 'C':
                    cout << "Round " << setw(4) << round << ": Pressed RIGHT. \n";
                    pressRight(); round++; break;
                case 'D':
                    cout << "Round " << setw(4) << round << ": Pressed LEFT. \n";
                    pressLeft(); round++; break;
            }
        max = find_max();
        }
    }
}




