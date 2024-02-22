# Requirements
 
1. Shall have GUI
	1. Game Board shall have a 3x3x3x3 board. 
    2. Score display.
    3. Timer that keeps track of game.
2. Shall have clickable number boxes that allow user to type input.
3. Shall randomize starting board at beginning of game.
4. Shall have easy, medium, and hard difficulty settings.
    1. Easy
        1. 40% (33 tiles) of the board will be complete.
    2. Medium
        1. 30% (25 tiles) of the board will be complete.
    3. Hard
        1. 21% (17 tiles) of the board will be complete.
5. Shall allow one hint per game.
    1. Hint consists of one tile being filled for the user.
6. Shall have a submit button which verifies if the given solution is correct.
    1. Can only be clicked when all cells are filled out.
    2. If correct:
        1. User shall receive summary of game.
    3. If incorrect:
        1. Incorrect boxes shall be highlighted indicating wrong moves.
        2. User shall have opportunity to try again with the incorrect entries removed or end game.
7. Various factors shall contribute to scoring.
    1. A correct game board after 1 attempt will reward 1000 points.
    2. Difficulty scoring:
        1. Easy mode shall be 0.5x the total score. 
        2. Medium shall be 1x the total score.
        3. Hard shall be 1.5x the toal score.
    3. 
