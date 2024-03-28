#include "../include/sudoku.h"

double scalarArr[] = {__EASY_SCALAR, __MEDIUM_SCALAR, __HARD_SCALAR};

void screenRefresh()
{
    std::system("clear");
    printf(__GAME_HEADER);
    return;
}

// cmdTable commands:---
void Game::quit()
{
    screenRefresh();
    printf("EXITING...");
    printf("Are you sure?\n0: \033[1;32mYES\033[0m\n1: \033[1;31mNO\033[0m\n");
    int choice = getInput();
    if (choice == 0)
    {
        std::system("clear");
        exit(0);
    }
    screenRefresh();
    return;
}
void Game::getHint()
{
}
void Game::solve()
{
    screenRefresh();

    printf("SOLVING...\nAre you sure?\n0: \033[1;32mYES\033[0m\n1: \033[1;31mNO\033[0m\n");
    int choice = getInput();
    if (choice == 0)
    { // solve board
        gameOver = true;
        NinebyNine solution = board.getSolution();
        for (int i = 0; i < __ROWS; i++)
        {
            for (int j = 0; j < __COLUMNS; j++)
            { // set values
                Tile current;
                current.row = i;
                current.column = j;
                current.value = solution.board[i][j];
                board.setTile(current);
            }
        }
    }
    // else:
    screenRefresh();
    return;
}
#ifdef CONFLICT_COLORING
void Game::refreshConflicts()
{
    for (int i = 0; i < __ROWS; i++)
    {
        for (int j = 0; j < __COLUMNS; j++)
        {
            Tile curr = board.getTile(i, j);

            board.checkForConflicts(curr);
        }
    }
}
#endif
void Game::enterSquare()
{
    Tile move;
    while (true)
    {
        printf("Please enter the Row[1-9]: ");
        move.row = (getInput() - 1);
        printf("Please enter the Column[1-9]: ");
        move.column = (getInput() - 1);
        printf("Please enter the Value: ");
        move.value = getInput();
        if ((move.row >= 0 && move.row < 9) &&
            (move.column >= 0 && move.column < 9) &&
            move.value >= 0 && move.column <= 9)
        { // check to see if not locked:
            int n = board.tileToInt(move);
            if (board.isLocked(n))
            {
                screenRefresh();
                std::cout << board << std::endl;
                printf("That tile cannot be changed!\n");
            }
            else
            {          // able to change the tile:
                break; // break out of the loop
            }
        }
        else
        {
            printf("Invalid options\n");
        }
    }
    board.setTile(move);
#ifdef CONFLICT_COLORING
    refreshConflicts();
#endif

    // refresh conflicts list

    return;
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
void printDifficulty()
{
    std::cout << "Please enter a difficulty:\n0:"
#ifdef COLOR_PRINT
              << "\033[5;31m"
#endif
              << " EXIT\n\033[0m1: "
#ifdef COLOR_PRINT
              << "\033[1;32m"
#endif
              << "Easy\n\033[0m2: "
#ifdef COLOR_PRINT
              << "\033[1;34m"
#endif
              << "Medium\n\033[0m3: "
#ifdef COLOR_PRINT
              << "\033[1;31m"
#endif
              << "Hard"
#ifdef COLOR_PRINT
              << "\033[0m"
#endif

              << std::endl;
    return;
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
    gameOver = false;
    board.generateBoard(difficulty);
    while (true)
    { // this is the game loop

        screenRefresh(); // clear screen
        std::cout << board << std::endl;
        if (gameOver)
        {
            printf("Thanks for playing!\n");
            break;
        }
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
        (this->*cmdTable[choice].func)(); // runs the command that was picked
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
    Game game;
    screenRefresh();
    int difficulty;
    while (true)
    {
        screenRefresh();
        if (false)
        {
        jumpWhenInvalid:
            screenRefresh();
            std::cout << "INVALID DIFFICULTY" << std::endl;
        }

        printDifficulty();

        difficulty = getInput();
        difficulty--;
        if (difficulty >= __EASY && difficulty <= __HARD)
        {
            game.setDifficulty(difficulty);
            game.setScoreScalar(scalarArr[difficulty]);
            break;
        }
        else if (difficulty == -1)
        {
            game.quit();
        }
        else
        {
            goto jumpWhenInvalid;
        }
    }
    // exit status is just the exit code that is returned
    // just like for main()
    int exitStatus = game.sudoku(); // function call to main() style function
    return 0 | exitStatus;          // bitwise OR to get true exit status
}
#endif