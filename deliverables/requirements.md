# Requirements
 
1. Sudoku game shall have GUI:
	1. Game Board shall have a 3x3x3x3 board. 
    2. Score display.
    3. Timer that keeps track of game.
2. Shall have clickable number boxes that allow user to type input.
3. Shall randomize starting board at beginning of game.
4. Shall have easy, medium, and hard difficulty settings.
    1. Easy:
        1. 33 tiles of the board will be complete.
    2. Medium:
        1. 25 tiles of the board will be complete.
    3. Hard:
        1. 17 tiles of the board will be complete.
5. Shall allow three hints per game.
    1. Hint consists of one tile being filled for the user.
6. Shall have a submit button which verifies if the given solution is correct.
    1. Button shall only be clicked when all cells are filled out.
    2. If board is correct:
        1. User shall receive summary of game.
    3. If board is incorrect:
        1. Incorrect boxes shall be highlighted indicating wrong moves.
        2. User shall have opportunity to try again with the incorrect entries cleared or end game.
7. The game shall keep a score.
    1. A correct game board after 1 attempt will reward 1000 points.
    2. Difficulty scoring:
        1. Easy mode shall be 0.5x the total score. 
        2. Medium shall be 1x the total score.
        3. Hard shall be 1.5x the toal score.
    3. Timer shall have score checkpoints:
        1. Any board solved in under 2 minutes shall grant 1000 points.
        2. After 5 minutes the user's score shall be set on an exponential decay rate.
    4. The user shall lose 300 points for each hint used.
    5. Points shall be rewarded/deducted at the submission of each board.
        1. For each correct tile the user shall receive 20 points.
        2. For each incorrect tile the user shall lose 20 points.