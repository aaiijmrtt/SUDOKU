#SUDOKU

solving the puzzle

The code in this repository presents a solution to the game of Sudoku, using a
simple backtracking algorithm. For those unfamiliar with the rules, the game is
played on a 9 \* 9 grid, each tile containing a digit. The grid is subdivided
into 9 smaller 3 \* 3 grids. Some of the tiles are already filled in. The
objective is to fill in the remaining tiles with digits between 1 and 9 subject
to the constraints that no row, column or subgrid contains the same digit twice.

**Instructions**:

1. **Compiling**: $gcc -o sudoku sudoku.c
2. **Using**: $./sudoku [grid]

**Arguments**:

* **grid**: [int[81]] the digits in the input grid: top to bottom, left to
right - blank tiles are zeroized.

**Note**:

* Requires gcc.
