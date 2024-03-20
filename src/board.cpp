#include "../include/board.h"

/* 
 *   difficulty passed in as int from user input
 *   0 = easy, 1 = medium, 2 = hard
 *   probably add nested for loop in initializer to fill out board (matrix)
 */ 
Board::Board(int difficulty)
{
    nTiles = 0;
    if (difficulty == 0)
     {
        scoreScalar = 0.5;
     }
    else if (difficulty == 1)
    {  
        scoreScalar = 1.0;
    }
    else
    {
        scoreScalar = 1.5;
    }
}


