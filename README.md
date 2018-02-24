# Samurai Sudoku
Saumurai, Hexadoku, Dodeka and Sudoku using Donald Knuth's Dancing
Links algorithm

Implementations in plain vanilla C++ of Donald Knuth's Dancing Links
algorith for Samurai Sudoku, Hexadoku, Dodeka Sudoku and Sudoku. I
investigated the use of smart pointers for the links, but decided as
it works just fine with raw pointers to leave it. I have made no
attempt to track and release the use of memory by the algorithm as the
programs just exit and release it all anyway.

## Samurai Sudoku
Samurai Sudoku puzzles are made up of five overlapping puzzles
like this:

	+---+---+---+   +---+---+---+
	|   |   |   |   |   |   |   |
	+---+---+---+   +---+---+---+
	|   | 1 |   |   |   | 2 |   |
	+---+---+---+---+---+---+---+
	|   |   | A |   | B |   |   |
	+---+---+---+---+---+---+---+
			|   | 3 |   |
	+---+---+---+---+---+---+---+
	|   |   | C |   | D |   |   |
	+---+---+---+---+---+---+---+
	|   | 4 |   |   |   | 5 |   |
	+---+---+---+   +---+---+---+
	|   |   |   |   |   |   |   |
	+---+---+---+   +---+---+---+

The slots in the four squares labelled A, B, C, D that overlap the
centre and outer four puzzles must be solved for both puzzles. These
puzzles can be found [here](http://samurai-sudoku.com).

## Hexadoku
Hexadoku puzzles use the digits 0-9,A-F in a 16x16 grid. The squares
are 4x4. These puzzles can be found [here](http://www.hexadoku.de).

	+---------+---------+---------+---------+
	|   6   1 |         | B     2 |   4     |
	| 0       | 3   E A |   D     |   C     |
	| 5       | 8       |         |     7 D |
	|   2 9   |       0 |     6   |       1 |
	+---------+---------+---------+---------+
	|   9     | B     3 | 5       |     1   |
	| 4 C 7 A | D     E |   3     |       9 |
	| 3 E 1   |   8   C | D   2   | 4     7 |
	|   F   8 | 5   0   |         |         |
	+---------+---------+---------+---------+
	|         |     D   |       6 |     0 8 |
	|   8 F   | E 4   6 |     3 9 |         |
	|       7 | 1       | F E   D |       C |
	| 6       |   0 C   | 2 4 5   |     E 3 |
	+---------+---------+---------+---------+
	|         |   C   1 | A       |     2   |
	| D       |     3 9 |     B   |   1     |
	|   4   6 | A       | E 5 1   |     3   |
	| F   A C | 6   B 7 |   9     |       0 |
	+---------+---------+---------+---------+

## Dodeka Sudoku
Dodeka Sudoku puzzles use the digits 0-9,A-B in a 12x12 grid. The squares
are 4x3. These were originally published in the UK Sunday Times.

	+---------+---------+---------+
	|   0     |     8   | 7   3   |
	|       9 |         | 5 4     |
	|         | B 4     |     9 0 |
	+---------+---------+---------+
	|   2 5   | 3   4   |   1     |
	| 0   6   |         |     A   |
	|       4 | 5   9   | 6     8 |
	+---------+---------+---------+
	| 7     0 |   2   B | A       |
	|   A     |         |   7   4 |
	|     B   |   1   9 |   8 2   |
	+---------+---------+---------+
	| A 3     |     B 6 |         |
	|     4 7 |         | 8       |
	|   B   5 |   3     |     6   |
	+---------+---------+---------+

## Sudoku puzzles
Sudoku puzzles are now published in a large number of magazines and
newspapers.

	+-------+-------+-------+
	|       |       |       |
	|     4 | 9   7 | 1     |
	|   7 8 | 5   1 | 6 4   |
	+-------+-------+-------+
	| 9     | 4   8 |     3 |
	|       |       |       |
	| 5     | 6   9 |     7 |
	+-------+-------+-------+
	|   3 9 | 1   4 | 5 2   |
	|     1 | 7   5 | 3     |
	|       |       |       |
	+-------+-------+-------+
