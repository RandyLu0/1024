//File name: /Users/laptopuser/Documents/cs135_codes/projects/game1024/TestBoard.cpp
#include <iostream>
#include "Board.hpp"
using namespace std;

int main()
{
    Board game(8, 3);
    game.print();

    //coloring output in console output in c++ in linux
    //https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
    //cout << "\x1B[31mTexting\033[0m\t\t\n";
    //print out red text "Texting"

    //game.start();
    return 0;
}
