#include "../include/board.h"

Board::Board(int difficulty):
{
    nTiles = 0;
    if (difficulty == 0)
        scoreScalar = 0.5;
    else if (difficulty == 1)
        scoreScalar = 1.0;
    else
        scoreScalar = 1.5;
}


