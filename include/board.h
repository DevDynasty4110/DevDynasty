#pragma once
#include <string>
#include <iostream>
// define preprocessor macros:
#define __EASY 0
#define __EASY_SCALAR 0.5
#define __MEDIUM 1
#define __MEDIUM_SCALAR 1.0
#define __HARD 2
#define __HARD_SCALAR 1.5
#define __COLUMNS 9
#define __ROWS 9
class Board
{
private:
    // represents the board with row and column constants
    uint board[__ROWS][__COLUMNS];
public:
    /// @brief default constructor
    Board();
    
    /// @brief customized constructor
    /// @param difficulty determine how many tiles are filled in to start game
    Board(int difficulty);
    
    /// @brief default destructor 
    ~Board(); 
    
    /// @brief print horizontal border to separate sudoku board
    void printHorizontal();
    
    /// @brief Overloading << operator to allow us to print the sudoku board
    /// with our formatting to the console
    /// @param os reference to ostream object to output the board to
    /// @param b Board object that is being printed
    friend std::ostream& operator<<(std::ostream &os, const Board& b);
};