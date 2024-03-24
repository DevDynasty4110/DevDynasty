#include "../include/board.h"

/*
 *   difficulty passed in as int from user input
 *   0 = easy, 1 = medium, 2 = hard
 *   probably add nested for loop in initializer to fill out board (matrix)
 */
Board::Board(int difficulty)
{
    nTiles = 0;
    if (difficulty == __EASY)
    {
        for (int i = 0; i < __ROW; ++i)
        {
            for (int j = 0; j < __COLUMN; ++j)
            {
                board[i][j] = i;
            }
        }
        scoreScalar = __EASY_SCALAR;
    }
    else if (difficulty == __MEDIUM)
    {
        scoreScalar = __MEDIUM_SCALAR;
    }
    else if (difficulty == __HARD_SCALAR)
    {
        scoreScalar = __HARD_SCALAR;
    }
    else
    {
        exit(-1); // invalid difficulty
    }
}

Board::~Board()
{
}

void printHorizontal()
{
    for (int i = 0; i < __COLUMN + 2; ++i)
    {
        if (i == 3 || i == 7)
        {
            std::cout << "|";
        }
        else {
            std::cout << "-";
        }
        std::cout << "\t";
    }
    std::cout << "\n";
}

std::ostream &operator<<(std::ostream &os, const Board &b)
{
    for (int i = 0; i < __ROW; ++i)
    {
        std::cout << "\n";
        if (i == 3 || i == 6)
        {
            printHorizontal();
            std::cout << "\n";
        }
        for (int j = 0; j < __COLUMN; ++j)
        {
            std::cout << b.board[i][j];
            std::cout << "\t";
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