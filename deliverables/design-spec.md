# Sudoku Design Specification

1. Utilize the C++ wxWidgets library:
    1. The sudoko board will be a 3x3x3x3 board. This board will be partially filled at the start of the game depending on the selected difficulty. The user will be able to fill in blank entries of the boards by clicking on the selected tile and entering a number 1-9 by keyboard. 
    2. The score display will be blank until the comlpeted board is submitted. The score will then be calculated and the score display interface will be updated. 
    3. The timer interface will update continuosly as the game progresses. Displaying to the player the amount of time they are taking to solve the suduoko puzzle.
2. The cells of the sudoku board will be divided up by boxes. These boxes will allow users to interact with them in two ways: clicking the box and typing a number into the box.
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
5. Hint counter keeps track of how many hints the user leverages.
    1. Hints will be given in order from left to right on the at the topmost row of the sudoku board.. 
6. Green submit button will reside at the bottom of the window.
    1. Program will check entire board to see if it has an empty cell and if it does button won't be able to be clicked.
    2. All entries are filled program checked for valid board:
        1. Window with time to complete, difficulty, and total score will be displayed. 
    3. Some entries are empty or board is not valid for sudoku:
        1. GUI will highlight in red all of the incorrect/empty cells.
        2. Game will continue and the incorrect/empty cells will be cleared ready for user input.
7. The game will calculate score based on various factors such as: number of hints used, number of incorrect submissions, time to solve, and difficulty selected.
    1. To implement the difficulty, the user will be prompted with 3 options. Easy, Medium, or Hard. This will be collected using a graphical interface handled by the front end team. However, the GUI will send the choice over to the game logic.
        1. Easy: the easy game mode will scale the total score by 0.5
        2. Medium: The medium game mode will scale the total score by 1.0 (no change)
        3. Hard: the hard game mode will scale the total score by 1.5
    2. A timer will continuously run that contributes to the score
        1. The score will be determined by an exponential decay function
            $F(t) = 1000e^{-α(t + T)}$  
            `α`: the decay rate  
            `t`: the time in seconds (Variable)  
            `T`: the time offset  
            The best found values are as follows:  
            $α = \frac{1}{60}$  
            `t` = t (variable)  
            `T` = -300  
            this produces:  
            $F(t) = 1000e^{-\frac{1}{60}(t -300)}$

    3. The base score will have 300 points subracted for every hint that is used
    4. Each incorrect submission divides user score by 1.5.
    5. Final score
        1. The final score will be calculated by taking the sum of the base score and the time bonus.
        The final score will look like this: 
        
        $Score = score_i + F(t)$  
        where $t \geq 300$