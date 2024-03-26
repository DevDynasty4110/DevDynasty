/* used this link for reference in how to randomize sudoku board
 * to allow for it to still be solvable
 * https://www.geeksforgeeks.org/program-sudoku-generator/
 */

#include "../include/board.h"
extern int nRemove[] = {__TOTAL_TILES - __N_TILES_EASY, __TOTAL_TILES - __N_TILES_MEDIUM, __TOTAL_TILES - __N_TILES_HARD};
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
            board[i][j] = 0;
    }
}

Board::~Board()
{
}

void Board::generateBoard(int difficulty)
{
    // Fill the diagonal of ROWS x COLUMNS matrices
    fillDiagonal();

    // Fill remaining blocks
    fillRemaining(0, SRR);

    // Remove Randomly difficulty digits to make game
    removeDigits(difficulty);
}

void Board::fillDiagonal()
{   // iterate through each row, increment i by square root
    // to keep place of diagonal in each row
    for (int i = 0; i < __ROWS; i = i + SRR)
    {

        // for diagonal box, start coordinates->i==j
        fillBox(i, i);
    }
}
// Returns false if given 3 x 3 block contains num.
bool Board::unUsedInBox(int rowStart, int colStart, int num)
{
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
// Fill a 3 x 3 matrix.
void Board::fillBox(int row, int col)
{
    int num;
    for (int i = 0; i < SRR; i++)
    {
        for (int j = 0; j < SRR; j++)
        {
            do
            {
                num = randomGenerator(__ROWS);
            } while (!unUsedInBox(row, col, num));
            board[row + i][col + j] = num;
        }
    }
}
// Random generator
int Board::randomGenerator(int num)
{
    return (int)floor(
        (float)(rand() / double(RAND_MAX) * num + 1));
}

// Check if safe to put in cell
bool Board::isSafe(int i, int j, int num)
{
    return (
        unUsedInRow(i, num) && unUsedInCol(j, num) && unUsedInBox(i - i % SRR, j - j % SRR, num));
}

// check in the row for existence
bool Board::unUsedInRow(int i, int num)
{
    for (int j = 0; j < __ROWS; j++)
    {
        if (board[i][j] == num)
        {
            return false;
        }
    }
    return true;
}

// check in the row for existence
bool Board::unUsedInCol(int j, int num)
{
    for (int i = 0; i < __ROWS; i++)
    {
        if (board[i][j] == num)
        {
            return false;
        }
    }
    return true;
}

// A recursive function to fill remaining
// matrix
bool Board::fillRemaining(int i, int j)
{
    // System.out.println(i+" "+j);
    if (j >= __ROWS && i < __ROWS - 1)
    {
        i = i + 1;
        j = 0;
    }
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
            i = i + 1;
            j = 0;
            if (i >= __ROWS)
            {
                return true;
            }
        }
    }
    for (int num = 1; num <= __ROWS; num++)
    {
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

// Remove the empty no. of digits to
// complete game
void Board::removeDigits(int empty)
{
    int count = empty;
    while (count != 0)
    {
        int cellId = randomGenerator(__ROWS * __COLUMNS) - 1;
        // System.out.println(cellId);
        // extract coordinates i and j
        int i = (cellId / __ROWS);
        int j = cellId % __ROWS;
        if (j != 0)
        {
            j = j - 1;
        }
        // System.out.println(i+" "+j);
        if (board[i][j] != 0)
        {
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