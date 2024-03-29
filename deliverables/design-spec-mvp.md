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
