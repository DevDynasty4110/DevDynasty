#include "../include/sudoku.h"

double scalarArr[] = {__EASY_SCALAR, __MEDIUM_SCALAR, __HARD_SCALAR};

// cmdTable commands:---
void Game::quit()
{
    std::system("clear");
    printf("EXITING...");
    printf("Are you sure?\n0: \033[1;32mYES\033[0m\n1: \033[1;31mNO\033[0m\n");
    int choice = getInput();
    if (choice == 0)
    {
        std::system("clear");
        exit(0);
    }
    return;
}
void Game::getHint()
{
}
void Game::solve()
{
}
void Game::enterSquare()
{
}
void Game::clearSquare()
{
}
void Game::submit()
{
}
//---------------------

int getInput()
{
    while (true)
    {
        int value = 0;
        if (!(std::cin >> value))
        {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear();                                                   // Clear the fail bit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
        else
        {
            return value;
        }
    }
}

void Game::printCmds()
{
    for (int i = 0; i < __N_COMMANDS; i++)
    {
        printf("%d: %s\n", i, cmdTable[i].name);
    }
}

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
    while (true)
    {
        std::system("clear"); // clear screen
        std::cout << board << std::endl;
        printCmds();
        int choice;
        while (true)
        {
            choice = getInput();
            if (choice >= 0 && choice < __N_COMMANDS)
                break;
            else
            {
                printf("Enter a valid choice\n");
            }
        }
        (this->*cmdTable[choice].func)();
    }
    return 0; // return 0 if exits properly
}

void Game::setScoreScalar(double s)
{
    scoreScalar = s;
}

#ifdef TERMINAL
int main()
{
    std::system("clear"); // clear screen
    Game game;
    int difficulty;
    while (true)
    {
        std::cout << "Please enter a difficulty:\n0:"
#ifdef COLOR_PRINT
                  << "\033[1;32m"
#endif
                  << " Easy\n\033[0m1: "
#ifdef COLOR_PRINT
                  << "\033[1;34m"
#endif
                  << "Medium\n\033[0m2: "
#ifdef COLOR_PRINT
                  << "\033[1;31m"
#endif
                  << "Hard\033[0m"

                  << std::endl;
        difficulty = getInput();
        if (difficulty >= __EASY && difficulty <= __HARD)
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