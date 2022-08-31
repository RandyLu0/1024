#ifndef BOARD_H
#define BOARD_H
#pragma once

class Board{
public:
    Board(); //construct a 3 x 3 panel
    Board(int m = 3); //construct a m x m panel
    Board(int m, int n); //construct a m x n panel
    void setGoal(int goal); //set goal of the game
    ~Board();
    void allocateMemory(); //dynamically allocate memory for panel so that panel has numRows rows and numCols columns
    void clear(); //set each cell of the panel to be zero
    void print() const; //print the panel
    void selectRandomCell(int& row, int& col); //select a random cell from empty cell
    //movement
    void pressUp();
    void pressDown();
    void pressLeft();
    void pressRight();
    void start(); //start the game
    bool noAdjacentSameValue() const; //return if there aren't two adjacent cells with same value
    int find_max() const;
private:
    int** panel; //two dimensional array with numRows rows and numCols columns
    int numRows; int numCols;
    int target; //what is the goal
    int max; //the current max in all cells of panel
};
#endif
