#pragma once
#include <iostream>
#include "../include/board.h"
#include <limits>

#define __EASY_SCALAR 0.5
#define __MEDIUM_SCALAR 1.0
#define __HARD_SCALAR 1.5

// define if using GUI or Terminal:
// YOU CAN ONLY HAVE 1 DEFINED AT A TIME!
// if you comment one out, uncomment the other
// please use comments, do not remove the line (for ease of use) -Liam

//---------------
//#define TERMINAL
#define GUI
//---------------

// for easy and quick access
#ifndef SCALAR_ARRAY
#define SCALAR_ARRAY
extern double scalarArr[];
#endif

// holds the row/column and the value for a game move
struct Move
{
    // how we will define moves
    uint row;
    uint column;
    uint value;
};

class Game
{
public:
    int sudoku(); // replacement for main()
    void startGame();
    // returns a completed board from the current unsolvded board
    Board autoSolve();
    Move getHint();                      // returns a move
    Board generateBoard(int difficulty); // please use difficulty macros here!
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