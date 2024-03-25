#pragma once
#include <iostream>
#include "../include/board.h"

// define if using GUI or Terminal:
// YOU CAN ONLY HAVE 1 DEFINED AT A TIME!
// if you comment one out, uncomment the other
// please use comments, do not remove the line for ease of use -Liam

//---------------
#define TERMINAL
// #define GUI
//---------------

class Game
{
public:
    void startGame();

private:
    Board gameBoard;
};