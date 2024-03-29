# Sudoku Design Specification (MVP)

1. The tiles that are chosen to be revealed at the start will be randomized as well as the actual numbers that will be in those tiles at the start of each game. A fully complete board will be constructed behind the scenes to ensure that each starting board is valid. The only component of the starting board that won't be random is every row, column, and square will have at least one entry.
2.  At start of each game the user wil have the opportunity to choose between easy, medium, and hard. Once the game is done generating the board for specified game mode it will iterate through each column, row, and square to verify that each component has at least one entry.
    1. Easy:
        1. Counter increments after each square is revealed, revelation process stops once counter hits 33.
    2. Medium:
        1. Counter increments after each square is revealed, revelation process stops once counter hits 25.
    3. Hard:
        1. Counter increments after each square is revealed, revelation process stops once counter hits 17.
3. Board and all other user interface will be displayed via std::cout and printf.
    1. Various text will be printed with ANSI color codes.
    2. Each option for user input printed to the screen will explain what the user needs to press to perform a function (ex: press 0 to quit).
    3. Header with ANSI color codes will be displayed to the screen for each step.
4. Various functions will be implemented for the user to alter the board state.
    1. Quit function that allows the user to exit() the program at any time.
    2. Move function that changes an empty space in the board to the number that the user entered. 
    3. Erase function that lets a user erase a previously entered value back to an empty one.
    4. Hint function that once is selected prints to the user what column, row, and value the given hint is to represent a "free" move.
    5. Submit button that compares the user's board to the initial board before the entries were removed to verify that they match.
    6. Solve function that displays the complete board to the user and ends the current game.

## Contributors
* Michael Sloan 
