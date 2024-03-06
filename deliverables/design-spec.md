# Sudoku Design Specification

1. GUI
    1. The sudoko board will be a 3x3x3x3 board. This board will be partially filled at the start of the game depending on the selected difficulty. The user will be able to fill in blank entries of the boards by clicking on the selected tile and entering a number 1-9 by keyboard. 
    2. The score display will be blank until the comlpeted board is submitted. The score will then be calculated and the score display interface will be updated. 
    3. The timer interface will update continuosly as the game progresses. Displaying to the player the amount of time they are taking to solve the suduoko puzzle.
2. GUI
3. The tiles that are chosen to be revealed at the start will be randomized as well as the actual numbers that will be in those tiles at the start of each game. A fully complete board will be constructed behind the scenes to ensure that each starting board is valid. The only component of the starting board that won't be random is every row, column, and square will have at least one entry.
4. At start of each game the user wil have the opportunity to choose between easy, medium, and hard using GUI for each option. Once the game is done generating the board for specified game mode it will iterate through each column, row, and square to verify that each component has at least one entry.

    **<ins>Mock up of the difficulty selection GUI:<ins>**

    ![Difficulty](../images/difficulty.png)

    1. Easy:
        1. Counter increments after each square is revealed, revelation process stops once counter hits 33.
    2. Medium:
        1. Counter increments after each square is revealed, revelation process stops once counter hits 25.
    3. Hard:
        1. Counter increments after each square is revealed, revelation process stops once counter hits 17.
5. Hint counter will decrement after user uses a hint. Once the user is out of hints, the button will not register a click.
    1. Random number generator will choose what tile gets filled on the board. 
6. Green submit button will reside at the bottom of the window.
    1. Program will check entire board to see if it has an empty cell and if it does button won't be able to be clicked.
    2. All entries are filled program checked for valid board:
        1. Window with time to complete, difficulty, and total score will be displayed. 
    3. Some entries are empty or board is not valid for sudoku:
        1. GUI will highlight in red all of the incorrect/empty cells.
        2. Game will continue and the incorrect/empty cells will be cleared ready for user input.
7. Backend
    1. When a game attempt is submitted, the game will determine if it is the first attempt of submission. if it is the first attempt and it is correct, it will award 1000 points to the user
    2. To implement the difficulty, the user will be prompted with 3 options. Easy, Medium, or Hard. This will be collected using a graphical interface handled by the front end team. However, the GUI will send the choice over to the game logic.
        1. Easy: the easy game mode will scale the total score by 0.5
        2. Medium: The medium game mode will scale the total score by 1.0 (no change)
        3. Hard: the hard game mode will scale the total score by 1.5
    3. A timer will continuously run contribute to the score
        1. if a board is solved in under 5 minutes, the game will add 1000 points to the total score
        2. Once 5 minutes has passed, this additional score will be determined by an exponential decay function
            $$
            F(t) = 1000e^{-α(t + T)}$
            $$
    4. 
    5. 
        1. 
        2. 
