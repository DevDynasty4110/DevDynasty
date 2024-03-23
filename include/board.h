#include <string>
#define __EASY 0
#define __EASY_SCALAR 0.5
#define __MEDIUM 1
#define __MEDIUM_SCALAR 1.0
#define __HARD 2
#define __HARD_SCALAR 1.5
class Board
{
private:
    int *board[][];
    int nTiles;
    double scoreScalar;

public:
    Board(); // default constructor
    Board(int difficulty);
    ~Board(); // default destructor
};