# Project-2-3-Quadris

Bonus Features:

1. Completing the entire project, without leaks, and without explicitly managing your own memory.

2. Command "aimode", which makes our AI play until the game is over.

- To enable this feature, use the flag -aimode
- EX: ./quadris -aimode
- Once the game starts, at any moment, you can use the command aimode to make the AI take over
- Note: aimode is only enabled for level 0-2 (not 3 and 4 due to heavy block constraint)

3. When the game is over, the UI displays "Game over. Try Again?"

- To enable this feature, use the flag -showGameOver
- EX: ./quadris -showGameOver
- When the game is over, you should see the text appear on top of the board.
- Enter "restart" at the command line to try again.

Further, our parser handles multipliers and shortcuts