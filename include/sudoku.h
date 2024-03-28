#pragma once
#include <iostream>
#include "../include/board.h"
#include <limits>

#define __EASY_SCALAR 0.5
#define __MEDIUM_SCALAR 1.0
#define __HARD_SCALAR 1.5

//print out at beginning of screen
#define __GAME_HEADER "\033[97;44m\
 ____  _   _ ____   ___  _  ___   _     \n\
/ ___|| | | |  _ \\ / _ \\| |/ / | | |    \n\
\\___ \\| | | | | | | | | | ' /| | | |    \n\
 ___) | |_| | |_| | |_| | . \\| |_| |    \n\
|____/ \\___/|____/ \\___/|_|\\_\\\\___/     \n\
 ______________________________________ \033[97;107m\n\
|______________________________________|\033[0m\n\n"


// define if using GUI or Terminal:
// YOU CAN ONLY HAVE 1 DEFINED AT A TIME!
// if you comment one out, uncomment the other
// please use comments, do not remove the line (for ease of use) -Liam

//---------------
#define TERMINAL
// #define GUI
//---------------

// for easy and quick access
#ifndef SCALAR_ARRAY
#define SCALAR_ARRAY
extern double scalarArr[];
#endif
class Game; // forward declaration
// holds the row/column and the value for a game move
struct Move
{
    // how we will define moves
    uint row;
    uint column;
    uint value;
};
struct Command
{
    const char *name;
    void (Game::*func)();
};
    int getInput(); //get integer input

class Game
{
public:
    // command table commands:
    void quit();
    void getHint();
    void solve();
    void enterSquare();
    void clearSquare();
    void submit();
    //-------------

    void printCmds(); // print all the commands
// cmdTable gives the ability to enter commands for user input
#define __N_COMMANDS 6
    Game() : cmdTable{
                 {"\033[5;31mQuit\033[0m", &Game::quit},
                 {"\033[1;32mSubmit\033[0m", &Game::submit},
                 {"Get hint", &Game::getHint},
                 {"Solve", &Game::solve},
                 {"Enter Square", &Game::enterSquare},
                 {"Clear Square", &Game::clearSquare}
                 } {}
    int sudoku(); // replacement for main()
    void startGame();
    // returns a completed board from the current unsolvded board
    Board autoSolve();
    Move generateHint(); // returns a move

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
    Command cmdTable[__N_COMMANDS];
    int difficulty;
    Board gameBoard;
    double scoreScalar;
    int nTiles;
};