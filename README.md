# AI-Optimal-Decision-in-Games
Sadık likes to play games. One of his favorite games is a turn-based sudoku game which is modified to be a two-player game. In this game, in each turn, a player picks one of the empty squares on the sudoku grid and writes one of the available numbers for that square. When there is not a valid move left, player who performs the last move wins the game. Since he is very bad at playing games, he likes to use a computer program to gain advantage against his opponents when playing a game. You need to help him by creating a minimax agent that finds the best move to play in a given game state. Your program is going to read initial game state from an input file. Some squares on the given sudoku grid is already occupied at the start.
The game has the following rules:
• Standard sudoku rules apply for numbers. That is, you can’t place a number if it already exists in the same row/column/box.
• A player can choose any empty square to make a move (if there is a valid number available for that square).
• Player who performed the last move wins the game.
You need to:
(a) Write a program that reads the game grid from an input file. 
(b) Implement a basic minimax agent to solve the game.
(c) Implement a minimax agent with alpha-beta pruning to solve the game. 
(d) Compare two agents in terms of:
• The number of nodes evaluated in the search tree 
• The running time
Some important aspects about your implementation:
• Your program will calculate the result for the first player (player max).
• For the assignment, you are required to implement the standard minimax algorithm, that is, your evaluation function will always evaluate a given position from the per- spective of the player max. If the player max is going to win the game from the given state, the utility of that state must be higher compared to utilities of losing states.
• Any other form of the minimax algorithm is not allowed and you will not get any grade.
• Do not use any heuristic functions for state evaluation. Value of states must be calcu- lated exactly by searching down to the game tree and propogating terminal state values appropriately.
• Your program must accept a command line argument, input file to read initial game state.
Input File Format
A text file with 9 lines, each line contains 9 space separated numbers. Each number represent the initial number of a square on the sudoku board. If a number is 0, it means that square is initially empty.
Output Format
You will only print a single digit. Print 1 if the first player is going to win, else 2.
Constraints
Normal sudoku constraints apply for placing numbers to the empty squares:
• Each number can only occur once in the same row
• Each number can only occur once in the same column
• Each number can only occur once in one of the 9 3x3 areas.
1 ≤ #empty squares in the given grid ≤ 15


Example input 0:
436100982 
521398467 
879260153 
642859371 
957413826 
080627094 
208741635 
705930240 
300502010
