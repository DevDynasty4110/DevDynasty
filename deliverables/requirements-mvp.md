# Sudoku Requirements (MVP)

1. Shall randomize starting board at beginning of game.
    - **Eval: will test by running several cases to make**
        **sure that it is random and evenly distributed**
2. Shall have easy, medium, and hard difficulty settings.
    1. Easy:
        1. 33 tiles of the board will be complete.
            - **Eval: will test to make sure that only 33 tiles are filled in**
    2. Medium:
        1. 25 tiles of the board will be complete.
            - **Eval: will test to make sure that only 25 tiles are filled in**
    3. Hard:
        1. 17 tiles of the board will be complete.
            - **Eval: will test to make sure that only 17 tiles are filled in**
3. Game shall be played in the terminal.
    - **Eval: will test by interacting with the game solely in the terminal**
    1. Shall incorporate various color schemes to the game.
        - **Eval: will test by ensuring there is color in the terminal window**
    2. Shall instruct user how to interact with the game at each step.
        - **Eval: will test by ensuring that there are instructions throughout entirety of game**
    3. Shall display sudoku header throughout entirety of game.
        - **Eval: will test by looking for header at each step of the game**
4. Shall be various modes of interaction for the user while playing
    1. Shall allow the user to quit at any given time.
        - **Eval: test to make sure there is a quit option that exits the game at all times** 
    2. Shall allow the user to make an entry to the board.
        - **Eval: make sure user can enter a number and it appears on the game board**
    3. Shall allow the user to erase their entry.
        - **Eval: ensure that after user has entered something they can erase it and it disappears from board**  
    4. Shall offer hints that tell the user the row, column, and value.
        - **Eval: test to make sure that the hint is valid and wasn't already filled in yet** 
    5. Shall allow user to submit their board when they are finished.
        - **Eval: test to ensure there is a submit option that checks validity of the user's board** 
    6. Shall allow user to solve entire board at once.
        - **Eval: make sure board is solved if user selects solve button** 

## Contributors
* Michael Sloan
* Liam Tolkkinen
* Samuel Medley