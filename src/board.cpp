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
