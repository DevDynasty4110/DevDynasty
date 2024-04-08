#include "../include/sudoku.h"
#include <sstream>

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

double pow(double x, int n) // return: x**n
{
    double result = 1.0;
    if (n == 0)
        return result;
    for (int i = 0; i < n; i++)
    {
        result *= x;
    }
    return result;
}
int fact(int x)
{ // recursive factorial function
    if (x == 0 || x == 1)
    {
        return 1; // base case
    }
    return (x * fact(x - 1));
}
int Game::calculateScore(time_t totalTime)
{
    // exponential decay function
    int n = 20; // number of iterations
    double result = COEFFICIENT;
    double x = (ALPHA) * (totalTime - T);
    double exponential = 0;
    for (int i = 0; i < n; i++)
    { // Taylor series for e^^x
        double numerator = pow(x, i);
        double denominator = fact(i);
        exponential += (numerator / denominator); // sum
    }
    result *= (1.0 / exponential);
    return static_cast<int>(result);
}

char *formatTime(int t)
{
    int minute = t / 60;
    int second = t % 60;
    char *result = new char[40];
    std::sprintf(result, "%dm, %ds", minute, second);
    return result;
}

void Game::getHint() {
    NinebyNine solution = board.getSolution();
    nHintsUsed++;
    for (int i = 0; i < __ROWS; i++) {
        for (int j = 0; j < __COLUMNS; j++) {
            Tile current = board.getTile(i, j);
            if (!current.value || current.value != solution.board[i][j]) {
                // Found an empty or incorrect tile
                Tile hint;
                hint.row = i;
                hint.column = j;
                hint.value = solution.board[i][j];  // Correct value from the solution

                board.setTile(hint);  // Update the board with the hint
                return; // Exit after providing the hint
            }
        }
    }
}

void Game::solve()
{
    screenRefresh();

    //printf("SOLVING...\nAre you sure?\n0: \033[1;32mYES\033[0m\n1: \033[1;31mNO\033[0m\n");
   // int choice = getInput();
   // if (choice == 0)
   // { // solve board
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
   // }
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

Tile Game::getMove(bool needValue)
{
    Tile move;
    while (true)
    {
        printf("Please enter the Row[1-9]: ");
        move.row = (getInput() - 1);
        printf("Please enter the Column[1-9]: ");
        move.column = (getInput() - 1);
        if (needValue)
        {
        enterValue:
            printf("Please enter the Value: ");
            move.value = getInput();
        }
        // check to make sure is valid:
        if ((move.row >= 0 && move.row < 9) &&
            (move.column >= 0 && move.column < 9))
        { // check to see if not locked:
            if (needValue && !(move.value >= 0 && move.value <= 9))
            {
                printf("invalid value!\n");
                goto enterValue; // get value again!
            }
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
    return move;
}

void Game::enterSquare()
{
    Tile move = getMove(true);
    board.setTile(move);
#ifdef CONFLICT_COLORING
    refreshConflicts();
#endif

    // refresh conflicts list

    return;
}
void Game::clearSquare()
{
    Tile move = getMove(false);
    move.value = 0; // zero will clear out the tile
    board.setTile(move);
}
void Game::submit()
{
    // check and compare to the solution
    NinebyNine solution = board.getSolution(); // use to compare
    for (int i = 0; i < __ROWS; i++)
    {
        for (int j = 0; j < __COLUMNS; j++)
        {
            Tile current = board.getTile(i, j);
            if (current.value != solution.board[i][j])
            { // incorrect!!
                nAttemptedSubmissions++;
                printf("Incorrect!\nUse a hint if you get stuck!\n");
                return;
            }
        }
    }
    // no collisions...
    printf("\033[1;32mCorrect!!\033[0m\n");
    gameOver = true;
    win = true;
        if (win) {
        time_t totalTime = time(nullptr) - startTime;
        int timeBonus = calculateScore(totalTime);

        if(totalTime < 300){
            timeBonus = 1000;
        }

        int subTotal = (1000 - (nHintsUsed * 300)) + timeBonus;
        int submitPenalty = subTotal;

        for(int i = 0; i < nAttemptedSubmissions; i++){
            submitPenalty /= 1.5;
        }

        submitPenalty = subTotal - submitPenalty;
        int hintDeduct = 300 * nHintsUsed;
        int finalSubTotal = subTotal - submitPenalty - hintDeduct;
        if(finalSubTotal < 0){
            finalSubTotal = 0;
        }
        finalScore = finalSubTotal * scalarArr[difficulty];
        return;
    }
    return;
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
{ // 2 columns instead of one
    int half = __N_COMMANDS / 2;
    for (int i = 0; i < half; i++)
    {
        if (i < __N_COMMANDS)
        {
            printf("%d: %s\t\t", i, cmdTable[i].name);
        }
        if (i + half < __N_COMMANDS)
        {
            printf("%d: %s\n", i + half, cmdTable[i + half].name);
        }
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
    startTime = time(nullptr);
}
// main() cant be defined if using a GUI
// Added an ifdef to determine which type of app it is

// Pre::Difficulty MUST be asserted before calling this function
int Game::sudoku()
{
    // initialize board:
    gameOver = false;
    win = false;

    board.generateBoard(difficulty);
    while (true)
    { // this is the game loop
        if (!win)
        {
            screenRefresh(); // clear screen
            std::cout << board << std::endl;
        }
        if (gameOver)
        {
            printf("Thanks for playing!\n");
            break;
        }
    skipRefresh:
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

        if (choice == 3 || (choice == 4 && !gameOver)) // hint or submit chosen
        {
            goto skipRefresh; // this is so that the hint doesn't
                              // get cleared off of the screen
        }
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