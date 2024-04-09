#pragma once
#include <iostream>
#include <cstdio>
#include "../include/board.h"
#include <limits>
#include <ctime>

#define __EASY_SCALAR 0.5
#define __MEDIUM_SCALAR 1.0
#define __HARD_SCALAR 1.5

#define MIN_PER_DECAY 8.0 // how many minutes per half life
#define ALPHA (1.0 / (MIN_PER_DECAY * 60.0))
#define T 300.0
#define COEFFICIENT 1000.0

// print out at beginning of screen
#define __GAME_HEADER "\033[97;44m\
\033[0m\t\t    \033[97;44m ____  _   _ ____   ___  _  ___   _     \n\
\033[0m\t\t    \033[97;44m/ ___|| | | |  _ \\ / _ \\| |/ / | | |    \n\
\033[0m\t\t    \033[97;44m\\___ \\| | | | | | | | | | ' /| | | |    \n\
\033[0m\t\t    \033[97;44m ___) | |_| | |_| | |_| | . \\| |_| |    \n\
\033[0m\t\t    \033[97;44m|____/ \\___/|____/ \\___/|_|\\_\\\\___/     \n\
\033[0m\t\t    \033[97;44m ______________________________________ \033[97;107m\n\
\033[0m\t\t    \033[97;107m|____________\033[5;34;107mBy DevDynasty\033[97;107m_____________|\033[0m\n\n"

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
int getInput(); // get integer input


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
    int finalScore;
    std::string aHint;
    Board board; //added to public
    bool win = false;
    time_t startTime;
    char *timeResult;
    //-------------
    #ifdef CONFLICT_COLORING
    void refreshConflicts();
    #endif

    void printCmds(); // print all the commands
    int calculateScore(time_t totalTime);
// cmdTable gives the ability to enter commands for user input
#define __N_COMMANDS 6
    Game() : cmdTable{
                 {"\033[5;31mQuit\t\033[0m", &Game::quit},
                 {"Enter Square", &Game::enterSquare},
                 {"Clear Square", &Game::clearSquare},
                 {"Get hint", &Game::getHint},
                 {"\033[1;32mSubmit\033[0m", &Game::submit},
                 {"Solve", &Game::solve}} {}
    int sudoku(); // replacement for main()
    void startGame();
    // returns a completed board from the current unsolvded board
    Board autoSolve();
    Move generateHint(); // returns a move
    Tile getMove(bool needVal);
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
    bool gameOver;
    int nHintsUsed=0;
    int nAttemptedSubmissions=0;
    //bool win;
    double scoreScalar;
    int nTiles;
};