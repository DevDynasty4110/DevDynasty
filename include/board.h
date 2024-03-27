#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
// define preprocessor macros:
#define __EASY 0
#define __MEDIUM 1
#define __HARD 2
#define __COLUMNS 9
#define __ROWS 9
#define __N_TILES_EASY 33
#define __N_TILES_MEDIUM 25
#define __N_TILES_HARD 17
#define __TOTAL_TILES (__ROWS * __COLUMNS)
#define __SRR 3 // square root of rows/columns (aka what smaller boxes will be)
extern int nRemove[];

class Board
{
private:
    // represents the board with row and column constants
    uint board[__ROWS][__COLUMNS];

    int SRR = __SRR;

public:
    /// @brief default constructor
    Board();

    /// @brief customized constructor
    /// @param difficulty determine how many tiles are filled in to start game
    Board(int difficulty);

    /// @brief default destructor
    ~Board();

    void autoSolve();

    /// @brief In the resource we used to generate a valid random
    /// sudoku board, they attakked the problem in a specific way.
    /// This attack was populate all of the diagonal 3x3 matrices first.
    /// Next recursively fill the rest of the matrices on the board.
    /// Lastly, once the matrix is fully populated, remove random number
    /// of elements for the user to solve.
    /// @param difficulty number of tiles for user to fill in
    void generateBoard(int difficulty);

    /// @brief Iterate through rows and fill diagonal of board
    void fillDiagonal();

    /// @brief used to check if smaller matrix has specific number in it
    /// @param rowStart row to start at for checking
    /// @param colStart column to start at for checking
    /// @param num specific number the function is checking for
    /// @return true if 3x3 doesn't contain num, false if it contains num
    bool unUsedInBox(int rowStart, int colStart, int num);

    /// @brief populate smaller matrix with numbers 1-9
    /// @param row specific row function starts at
    /// @param col specific column function starts at
    void fillBox(int row, int col);

    /// @brief find random number between 1 and num
    /// @param num max number to be generated
    /// @return random number between 1 and num
    int randomGenerator(int num);

    /// @brief verify num is able to be placed in position
    /// @param i row position
    /// @param j column position
    /// @param num number that is being placed
    /// @return true if number hasn't been used in row, column or box,
    /// and false if it has
    bool isSafe(int i, int j, int num);

    /// @brief check if num is already in row
    /// @param i row to check
    /// @param num num to check
    /// @return true if num isn't in row, false if it is
    bool unUsedInRow(int i, int num);

    /// @brief check if num is already in column
    /// @param j column to check
    /// @param num num to check
    /// @return true if num isn't in column, false if it is
    bool unUsedInCol(int j, int num);

    /// @brief recursive function to fill remaining matrix outside of
    /// diagonal
    /// @param i row to work on
    /// @param j column to work on
    /// @return true if it can be filled, false if it is complete
    bool fillRemaining(int i, int j);

    /// @brief Check the row, column, and sub-Box to see if removing tile(row, column)
    ///        would clear out an entire row/column/box.
    /// @param row The corresponding row of the selected tile
    /// @param column The corresponding column of the selected tile
    /// @return Returns True if removing tile(row, column) will clear
    ///         an entire row/column/box
    bool willClear(int row, int column);

    /// @brief remove num number of digits
    /// @param num number of digits to be removed from the board
    /// for user to solve
    void removeDigits(int num);

    /// @brief print horizontal border to separate sudoku board
    void printHorizontal();

    /// @brief Overloading << operator to allow us to print the sudoku board
    /// with our formatting to the console
    /// @param os reference to ostream object to output the board to
    /// @param b Board object that is being printed
    friend std::ostream &operator<<(std::ostream &os, const Board &b);
};