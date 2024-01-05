# Tic Tac Toe Game

## Overview

A simple console-based Tic Tac Toe game implemented in C++. The game allows you to play against a computer opponent using the minimax algorithm.

It also uses alpha-beta pruning to improve performance at a better depth

## How to Run

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-username/tic-tac-toe.git
   cd tic-tac-toe
   ```

2. **Compile and Run:**
   ```bash
   g++ main.cpp -o tic_tac_toe
   ./tic_tac_toe
   ```

## Gameplay

- The game is played on an NxN grid.
- You play as 'X' and the computer plays as 'O'.
- To make a move, enter the row and column indices when prompted.
- The game ends when a player wins, loses, or it's a tie.

## Code Structure

- The main code is in the `main.cpp` file.
- The game logic is implemented in the `Game` class.


## Dependencies

- C++ compiler (gcc recommended)

## Notes

- Adjust the `boardSize` and `maxDepth` variables in the `main.cpp` file to change the size of the board and the difficulty level.
- Ensure you have a C++ compiler installed on your system.

Enjoy the game! 🎮👾