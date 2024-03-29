/* used this link for reference in how to randomize sudoku board
 * to allow for it to still be solvable
 * https://www.geeksforgeeks.org/program-sudoku-generator/
 */

#include "../include/board.h"
int nRemove[] = {__TOTAL_TILES - __N_TILES_EASY, __TOTAL_TILES - __N_TILES_MEDIUM, __TOTAL_TILES - __N_TILES_HARD};
double floor(double x)
{                            // return truncated value
    return (double)((int)x); // truncate and then cast back to double
}
/*
 *   difficulty passed in as int from user input
 *   0 = easy, 1 = medium, 2 = hard
 */
Board::Board()
{

    for (int i = 0; i < __ROWS; i++)
    {
        for (int j = 0; j < __COLUMNS; j++)
        {
            board[i][j] = 0; // empty board
#ifdef CONFLICT_COLORING
            conflicts[i][j] = false; // set all conflicts to false
#endif
        }
    }
}

Board::~Board()
{
    // i have this commented out because it throws a seg fault...
    //  delete[] lockedTiles;
}
Tile::Tile() : row(0), column(0), value(0) {}

NinebyNine Board::getSolution()
{
    NinebyNine result;
    for (int i = 0; i < __ROWS; i++)
    {
        for (int j = 0; j < __COLUMNS; j++)
        {
            result.board[i][j] = solution[i][j];
        }
    }
    return result;
}

bool Board::isLocked(int n) const
{
    // binary search since lockedTiles is already sorted!
    // define start and end search indexes
    int start = 0;
    int end = nTiles;
    while (start <= end)
    {
        int indx = ((end - start) / 2) + start; // calculate midpoint (search point)

        if (lockedTiles[indx] == n)
        { // found!!
            return true;
        }
        if (lockedTiles[indx] < n)
        {                     // search upper sector
            start = indx + 1; // shrink lower bound
        }
        else
        {                   // search lower sector:
            end = indx - 1; // move lower bound up
        }
    }
    // n not found in array:
    return false;
}
#ifdef CONFLICT_COLORING
bool Board::checkForConflicts(Tile tile)
{

    // check row:
    for (int i = 0; i < __COLUMNS; i++)
    {
        if (board[tile.row][i] == tile.value && (i != tile.column))
        { // conflict!
            conflicts[tile.row][tile.column] = true;
            return true;
        }
    }
    // check column:
    for (int i = 0; i < __ROWS; i++)
    {
        if (board[i][tile.column] == tile.value && (i != tile.row))
        {
            conflicts[tile.row][tile.column] = true;
            return true;
        }
    }
    // check box
    int boxStartRow = (tile.row / __ROWS) * SRR;
    int boxStartCol = (tile.column / __COLUMNS) * SRR;

    for (int r = boxStartRow; r < boxStartRow + SRR; r++)
    {
        for (int c = boxStartCol; c < boxStartCol + SRR; c++)
        {
            if (board[r][c] == tile.value && !(r == tile.row && c == tile.column))
            {
                conflicts[tile.row][tile.column] = true;

                return true;
            }
        }
    }

    // no conflicts:
    conflicts[tile.row][tile.column] = false;
    return false;
}
#endif
int Board::getDifficulty()
{
    return difficulty;
}

int Board::getnTiles()
{
    return nTiles;
}

Tile Board::getTile(int n)
{
    Tile result;
    result.row = n / __COLUMNS;
    result.column = n % __ROWS;
    result.value = board[result.row][result.column];
    return result;
}
int Board::tileToInt(Tile &tile)
{
    return (tile.row * __ROWS) + tile.column;
}
void Board::setTile(Tile &tile)
{
    board[tile.row][tile.column] = tile.value;
}
Tile Board::getTile(int r, int c)
{
    Tile result;
    result.row = r;
    result.column = c;
    result.value = board[r][c];
    return result;
}

void Board::generateBoard(int dif)
{
    nTiles = __TOTAL_TILES - nRemove[dif];
    difficulty = dif;
    lockedTiles = new int[nTiles]; // dynamically allocated, must use destructor

    // Fill the diagonal of ROWS x COLUMNS matrices
    fillDiagonal();

    // Fill remaining blocks
    fillRemaining(0, SRR);

    // set solution before removing digits:
    for (int i = 0; i < __ROWS; i++)
    {
        for (int j = 0; j < __COLUMNS; j++)
        {
            solution[i][j] = board[i][j];
        }
    }

    // Remove Randomly difficulty digits to make game
    removeDigits(nRemove[dif]);

    // set remaining digits to be locked in place
    int indx = 0; // placeholder for the working index
    for (int i = 0; i < __TOTAL_TILES; i++)
    {
        Tile current = getTile(i);
        if (current.value) // if not zero:
        {
            lockedTiles[indx] = i; // add i value to locked tiles
            // lockedTiles will be sorted
            indx++;
        }
    }
}

void Board::fillDiagonal()
{ // iterate through each row, increment i by square root
    // to keep place of diagonal in each row
    for (int i = 0; i < __ROWS; i += SRR)
    {
        // fill smaller matrix
        fillBox(i, i);
    }
}

bool Board::unUsedInBox(int rowStart, int colStart, int num)
{ // iterate through smaller matrix
    for (int i = 0; i < SRR; i++)
    {
        for (int j = 0; j < SRR; j++)
        {
            if (board[rowStart + i][colStart + j] == num)
            {
                return false;
            }
        }
    }
    return true;
}

void Board::fillBox(int row, int col)
{
    // using a shuffled array made much faster runtime!
    int nineArr[9];
    for (int i = 1; i < 10; i++)
    {
        nineArr[i - 1] = i;
    }
    // shuffle
    for (int i = 8; i >= 0; i--)
    { // count down
        // swap with random index
        int swp = randomGenerator(i);
        int temp = nineArr[swp];
        nineArr[swp] = nineArr[i];
        nineArr[i] = temp;
    }

    // iterate through smaller matrix
    for (int i = 0; i < SRR; i++)
    {
        for (int j = 0; j < SRR; j++)
        {
            // use the preshuffled array instead of guessing
            // and checking to see if it already exists in the box
            board[row + i][col + j] = nineArr[(SRR * i) + j];
        }
    }
}

int Board::randomGenerator(int num)
{
    static bool seeded = false; // static allows for this variable to be unimutable
    if (!seeded)
    {
        srand(static_cast<unsigned int>(time(0))); // seeds the random generator

        seeded = true;
    }
    // updated randomGenerator line
    return static_cast<int>(floor((static_cast<float>(rand()) / RAND_MAX) * num));
}

bool Board::isSafe(int i, int j, int num)
{
    return ( // verify the number hasn't been used in row, column, or box (smaller matrix)
        unUsedInRow(i, num) && unUsedInCol(j, num) && unUsedInBox(i - i % SRR, j - j % SRR, num));
}

bool Board::unUsedInRow(int i, int num)
{ // iterate through row
    for (int j = 0; j < __ROWS; j++)
    {
        if (board[i][j] == num)
        {
            return false;
        }
    }
    return true;
}

bool Board::unUsedInCol(int j, int num)
{ // iterate through column
    for (int i = 0; i < __ROWS; i++)
    {
        if (board[i][j] == num)
        {
            return false;
        }
    }
    return true;
}

bool Board::fillRemaining(int i, int j)
{ // increment i and reset j because j has reached max
    if (j >= __ROWS && i < __ROWS - 1)
    {
        i++;
        j = 0;
    } // iterated through all columns and rows, nothing lef return true
    if (i >= __ROWS && j >= __ROWS)
    {
        return true;
    }
    if (i < SRR)
    {
        if (j < SRR)
        {
            j = SRR;
        }
    }
    else if (i < __ROWS - SRR)
    {
        if (j == (int)(i / SRR) * SRR)
        {
            j = j + SRR;
        }
    }
    else
    {
        if (j == __ROWS - SRR)
        {
            i++;
            j = 0;
            if (i >= __ROWS)
            {
                return true;
            }
        }
    } // iterate through each possible number (1-9)
    for (int num = 1; num <= __ROWS; num++)
    { // if num can be put in position, do it
        // and move to the next position
        if (isSafe(i, j, num))
        {
            board[i][j] = num;
            if (fillRemaining(i, j + 1))
            {
                return true;
            }
            board[i][j] = 0;
        }
    }
    return false;
}
bool Board::willClear(int row, int column)
{
    // becomes false if it finds another tile in search sector---
    bool soloRow = true;
    bool soloCol = true;
    bool soloBox = true;
    //----
    // search row:
    for (int i = 0; i < __COLUMNS; i++)
    {
        if (board[row][i] && (i != column))
        {
            soloRow = false;
            break;
        }
    }
    // search column:
    for (int i = 0; i < __ROWS; i++)
    {
        if (board[i][column] && (i != row))
        {
            soloCol = false;
            break;
        }
    }
    // search box:
    // determine what box to look for
    int boxColStart = (column / 3) * 3;
    int boxRowStart = (row / 3) * 3;

    for (int r = boxRowStart; r < boxRowStart + 3; r++)
    {
        for (int c = boxColStart; c < boxColStart + 3; c++)
        {
            if (board[r][c] != 0 && !(r == row && c == column))
            {
                soloBox = false;
                goto endTest; // break out of both loops and end test
            }
        }
    }
endTest: // label to jump to
    return (soloRow || soloCol || soloBox);
}

void Board::removeDigits(int count)
{

    // loop while there are still tiles to be removed
    while (count != 0)
    {
        int cellId = randomGenerator(__ROWS * __COLUMNS);
        // extract coordinates i and j
        int i = (cellId / __ROWS);
        int j = cellId % __ROWS;
        // if tile isn't empty, make it empty
        // willclear() tests to see if it will clear out the entire row/column/box
        // printf("Candidate: (%d, %d)\n", i, j);

        bool safeToClear = !willClear(i, j);
        if (board[i][j] != 0 && safeToClear)
        {
            // printf("Cleared tile(%d, %d)\n", i, j);
            count--;
            board[i][j] = 0;
        }
    }
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
#define __CELL_WIDTH 3
#define __PAD "       "  // 7spaces
#define __MED_PAD "   "  // 3spaces
#define __SMALL_PAD "  " // 2spaces
#ifdef OLD_BOARD
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
            if (b.board[i][j] != 0)
            {
// print with color
#ifdef COLOR_PRINT
                int n = (__ROWS * i) + j;
                std::cout << ((b.isLocked(n)) ? "\033[1;34m" : "\033[0m"); // prints blue digit if locked
#ifdef CONFLICT_COLORING
                std::cout << (b.conflicts[i][j] ? "\033[1;31m" : ""); // prints in red if conflicting value
#endif
#endif
                std::cout << b.board[i][j];
#ifdef COLOR_PRINT
                std::cout << "\033[0m";
#endif
            }
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
#endif

#ifdef NEW_BOARD
    std::cout << __PAD; // pad from the wall
    for (int i = 0; i < __ROWS; i++)
    { // generate indexes
        std::cout << i + 1 << __PAD;
    }
    std::cout << std::endl
              << "  |"; // left edge w/o index
    for (int i = 0; i < (__ROWS - 1) * __CELL_WIDTH; i++)
    {
        std::cout << "---"; // divider
    }
    std::cout << "|\n"; // end of divider
    // print out
    for (int i = 0; i < __ROWS * __CELL_WIDTH; i++)
    {
        if (i % __CELL_WIDTH == 0) // print indexes
        {
            std::cout << ((i + 1) / __CELL_WIDTH) + 1 << " |" << __SMALL_PAD << __SMALL_PAD;
            // print out contents:
            for (int j = 0; j < __ROWS * __CELL_WIDTH; j++)
            {
                if (j % __CELL_WIDTH == 0)
                {
                    std::cout << 0    //(3 * i) + (j / 3)
                              << " "; // number placeholder
                }
                else if ((j + 1) % __ROWS == 0)
                {
                    std::cout << "|" << __MED_PAD;
                }
                else if (j % __ROWS > 6)
                {
                    std::cout << __SMALL_PAD;
                }
                else
                {
                    std::cout << __MED_PAD;
                }
            }
        }
        else if ((i + 1) % __ROWS == 0 && i != 0) // horizontal lines
        {
            std::cout << "  |";
            for (int j = 0; j < (__ROWS - 1) * (__CELL_WIDTH); j++)
            {
                std::cout << "---";
            }
            std::cout << "|";
            if (i != (__ROWS * __CELL_WIDTH) - 1)
            {
                std::cout << "\n  | ";
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 23; k++)
                    {
                        std::cout << " ";
                    }
                    std::cout << "|";
                }
            }
        }
        else
        {
            std::cout << "  | ";
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 23; k++)
                {
                    std::cout << " ";
                }
                std::cout << "|";
            }
        }
        std::cout << "\n";
    }

#endif
    return os;
}