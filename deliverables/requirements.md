# Requirements
 
1. Sudoku game shall have GUI:
	1. Game Board shall have a 9x9 board.
        -**Eval: will be evaluated by visual inspection**
    2. Shall display user score at end of the game.
        -**Eval: will check to see if score matches what we calulated at the end of the game**
    3. Timer that keeps track of game.
        -**Eval: will check to see if timer matches what we timed by hand for multiple games**
2. Shall have interactive tiles that allow user to type input directly.
    -**Eval: will test by clicking and entering values into boxes**
3. Board shall randomize at beginning of each game.
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
5. Shall allow hints for each game
    1. Hint consists of one tile being filled for the user.
        -**Eval: shall test to make sure that the hint is valid and wasn't already filled in yet**
6. Shall have a submit button which verifies if the user's proposed matches the randomly generated one.
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
    1. Difficulty scoring:
        -**Eval: for each: set the difficulty and then check the score afterwards**
        1. Easy mode shall be 0.5x the total score. 
        2. Medium shall be 1x the total score.
        3. Hard shall be 1.5x the toal score.
    2. Timer shall have score checkpoints:
        -**Eval: periodic testing to make sure that score checkpoints are synced**
        1. Awards a time bonus based on the following function.
            $F(t) = 1000e^{-α(t + T)}$
            -**Eval: test using a function that computes the score as f(t), f(t) being a function of time**
    3. The user shall lose 300 points for each hint used.
        -**Eval: test to see if 300 points are deducted for every hint used**
    4. Points shall be rewarded/deducted at the submission of each board.
    5. Final score
        1. The final score will be calculated at the end of the game