#include "../include/sudoku.h"

void Game::startGame()
{
    // TODO
}
// main() cant be defined if using a GUI
// Added an ifdef to determine which type of app it is
#ifdef TERMINAL
int main()
{
    Board board(__EASY);
    std::cout << board << std::endl;
    return 0;
}
#endif