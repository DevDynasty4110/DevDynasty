#include "../include/board.h"

/*
 *   difficulty passed in as int from user input
 *   0 = easy, 1 = medium, 2 = hard
 *   probably add nested for loop in initializer to fill out board (matrix)
 *   TODO:: add logic for random values between 1-9 to fill in board and verify
 *   that the board is actually solvable
 */
Board::Board()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            board[i][j] = 0;
    }
}

Board::~Board()
{
}

void printHorizontal()
{ // iterate through each column + 2 because of | borders for the sudoku board
    for (int i = 0; i < __COLUMNS + 2; ++i)
    { // add vertical border instead in 2 cases
        if (i == 3 || i == 7)
        {
            std::cout << "|";
        }
        else
        { // else print horizontal border
            std::cout << "-";
        }
        std::cout << "\t";
    }
    std::cout << "\n";
}

std::ostream &operator<<(std::ostream &os, const Board &b)
{ // iterate through entire matrix to print to console
    for (int i = 0; i < __ROWS; ++i)
    {
        std::cout << "\n";
        // print the horizontal border in these two cases
        // to properly split up sudoku board into 9 boxes with 9 tiles each
        if (i == 3 || i == 6)
        {
            printHorizontal();
            std::cout << "\n";
        }
        for (int j = 0; j < __COLUMNS; ++j)
        { // print actual value
            std::cout << b.board[i][j];
            std::cout << "\t";

            // print vertical border in these two cases
            if (j == 2 || j == 5)
            {
                std::cout << "|";
                std::cout << "\t";
            }
        }
        std::cout << "\n";
    }
    return os;
}