#include <string>
#include <iostream>
#define __EASY 0
#define __EASY_SCALAR 0.5
#define __MEDIUM 1
#define __MEDIUM_SCALAR 1.0
#define __HARD 2
#define __HARD_SCALAR 1.5
#define __COLUMN 9
#define __ROW 9
class Board
{
private:
    int board[__ROW][__COLUMN];
    int nTiles;
    double scoreScalar;

public:
    Board(); // default constructor
    Board(int difficulty);
    ~Board(); // default destructor
    void printHorizontal();
    friend std::ostream& operator<<(std::ostream &os, const Board& b);
};