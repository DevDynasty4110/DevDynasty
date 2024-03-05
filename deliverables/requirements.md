# Requirements
 
1. Sudoku game shall have GUI:
	1. Game Board shall have a 3x3x3x3 board.
        -**Eval: will be evaluated by visual inspection**
    2. Score display.
        -**Eval: will check to see if score updates properly with input**
    3. Timer that keeps track of game.
        -**Eval: will check to see if timer starts correctly,**
            **continuously runs, and stops when the game stops**
2. Shall have clickable number boxes that allow user to type input.
    -**Eval: will test by clicking and entering values into boxes**
3. Shall randomize starting board at beginning of game.
    -**Eval: will test by running several cases to make**
        **sure that it is random and evenly distributed**
4. Shall have easy, medium, and hard difficulty settings.
    1. Easy:
        1. 33 tiles of the board will be complete.
            -**Eval: will test to make sure that only 33 tiles are filled in**
    2. Medium:
        1. 25 tiles of the board will be complete.
            -**Eval: will test to make sure that only 25 tiles are filled in**
    3. Hard:
        1. 17 tiles of the board will be complete.
            -**Eval: will test to make sure that only 17 tiles are filled in**
5. Shall allow three hints per game.
    1. Hint consists of one tile being filled for the user.
        -**Eval: shall test to make sure that the hint is valid and wasn't already filled in yet**
6. Shall have a submit button which verifies if the given solution is correct.
    1. Button shall only be clicked when all cells are filled out.
    -**Eval: test to make sure nothing happens when button is clicked pre-maturely**
    2. If board is correct:
        -**Eval: test to make sure that there are no duplicates in a row, column or box**
        1. User shall receive summary of game.
            -**Eval: test to see if summary is correct by looking at hints and timer**
    3. If board is incorrect:
        -**Eval: test using purposely incorrect boards to see if the game catches it**
        1. Incorrect boxes shall be highlighted indicating wrong moves.
            -**test to see if the previously incorrect board highlights the second and greater occurences of the duplicate number in a row/column/box**
        2. User shall have opportunity to try again with the incorrect entries cleared or end game.
            -**Eval: Test to make sure that the game gives the dialogue box**
                --**Eval: Test to make sure that the buttons execute the proper function**
7. The game shall keep a score.
    1. A correct game board after 1 attempt will reward 1000 points.
        -**Eval: test using correct game board to verify 1000 points are awarded on the first try**
    2. Difficulty scoring:
        -**Eval: for each: set the difficulty and then check the score afterwards**
        1. Easy mode shall be 0.5x the total score. 
        2. Medium shall be 1x the total score.
        3. Hard shall be 1.5x the toal score.
    3. Timer shall have score checkpoints:
        -**Eval: periodic testing to make sure that score checkpoints are synced**
        1. Any board solved in under 5 minutes shall grant 1000 points.
            -**Eval: test at 5 minutes to see if score is 1000X(Difficulty scalar)**
        2. After 5 minutes the user's score shall be set on an exponential decay rate.
            -**Eval: test using a function that computes the score as f(t), f(t) being a function of time**
    4. The user shall lose 300 points for each hint used.
        -**Eval: test to see if 300 points are deducted for every hint used**
    5. Points shall be rewarded/deducted at the submission of each board.
        1. For each correct tile the user shall receive 20 points.
        2. For each incorrect tile the user shall lose 20 points.