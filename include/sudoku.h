#pragma once
#include <iostream>
#include "../include/board.h"
#include <limits>

// define if using GUI or Terminal:
// YOU CAN ONLY HAVE 1 DEFINED AT A TIME!
// if you comment one out, uncomment the other
// please use comments, do not remove the line (for ease of use) -Liam

//---------------
#define TERMINAL
// #define GUI
//---------------

class Game
{
public:
    int sudoku(); // replacement for main()
    void startGame();
    int getDifficulty();
    void setDifficulty(int dif)
    {
        difficulty = dif;
    }
    double getScoreScalar()
    {
        return scoreScalar;
    }
    void setScoreScalar(double s);
    int getNTiles()
    {
        return nTiles;
    }
    void setNTiles(int nT)
    {
        nTiles = nT;
    }

private:
    int difficulty;
    Board gameBoard;
    double scoreScalar;
    int nTiles;
};