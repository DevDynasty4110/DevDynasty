#include "../include/sudoku.h"

double scalarArr[] = {__EASY_SCALAR, __MEDIUM_SCALAR, __HARD_SCALAR};

void Game::startGame()
{
    // TODO
}
// main() cant be defined if using a GUI
// Added an ifdef to determine which type of app it is

// Pre::Difficulty MUST be asserted before calling this function
int Game::sudoku()
{
    // initialize board:
    Board board;
    board.generateBoard(difficulty);
    std::cout << board << std::endl;

    return 0; // return 0 if exits properly
}

void Game::setScoreScalar(double s)
{
    scoreScalar = s;
}

#ifdef TERMINAL
int main()
{
    Game game;
    int difficulty;
    while (true)
    {
        std::cout << "Please enter a difficulty:\n0: Easy\n1: Medium\n2: Hard" << std::endl;
        if (!(std::cin >> difficulty))
        {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear();                                                   // Clear the fail bit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
        else if (difficulty >= __EASY && difficulty <= __HARD)
        {
            game.setDifficulty(difficulty);
            game.setScoreScalar(scalarArr[difficulty]);
            break;
        }
        else
        {
            std::cout << "INVALID DIFFICULTY" << std::endl;
        }
    }
    // exit status is just the exit code that is returned
    // just like for main()
    int exitStatus = game.sudoku(); // function call to main() style function
    return 0 | exitStatus;          // bitwise OR to get true exit status
}
#endif