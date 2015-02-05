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

The slots in the four squares labelled A, B, C, D that overlap
the centre and outer four puzzles must be solved for both
puzzles.

The implementation I did in Java some years ago works just fine,
this one crashes:

	Program received signal SIGSEGV, Segmentation fault.
	0x004026d4 in Column::cover (this=0x8c2cf0) at DancingLinks.cpp:420
	420		    j->c->s--;
	(gdb) print j
	$1 = (Node *) 0x8c2f68
	(gdb) print j->c
	$2 = (Column *) 0x0
	(gdb) 

It's found a node with a null column while building the matrix.

## Hexadoku
Hexadoku puzzles use the digits 0-9,A-F in a 16x16 grid. The squares
are 4x4.

<style>
td {padding: 0 7px;}
table td {border: 2px solid black}
</style>
<table>
<tr><td> </td><td>6</td><td> </td><td>1</td><td> </td><td> </td><td> </td><td> </td><td>B</td><td> </td><td> </td><td>2</td><td> </td><td>4</td><td> </td><td> </td></tr>
<tr><td>0</td><td> </td><td> </td><td> </td><td>3</td><td> </td><td>E</td><td>A</td><td> </td><td>D</td><td> </td><td> </td><td> </td><td>C</td><td> </td><td> </td></tr>
<tr><td>5</td><td> </td><td> </td><td> </td><td>8</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>7</td><td>D</td></tr>
<tr><td> </td><td>2</td><td>9</td><td> </td><td> </td><td> </td><td> </td><td>0</td><td> </td><td> </td><td>6</td><td> </td><td> </td><td> </td><td> </td><td>1</td></tr>
<tr><td> </td><td>9</td><td> </td><td> </td><td>B</td><td> </td><td> </td><td>3</td><td>5</td><td> </td><td> </td><td> </td><td> </td><td> </td><td>1</td><td> </td></tr>
<tr><td>4</td><td>C</td><td>7</td><td>A</td><td>D</td><td> </td><td> </td><td>E</td><td> </td><td>3</td><td> </td><td> </td><td> </td><td> </td><td> </td><td>9</td></tr>
<tr><td>3</td><td>E</td><td>1</td><td> </td><td> </td><td>8</td><td> </td><td>C</td><td>D</td><td> </td><td>2</td><td> </td><td>4</td><td> </td><td> </td><td>7</td></tr>
<tr><td> </td><td>F</td><td> </td><td>8</td><td>5</td><td> </td><td>0</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td></tr>
<tr><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>D</td><td> </td><td> </td><td> </td><td> </td><td>6</td><td> </td><td> </td><td>0</td><td>8</td></tr>
<tr><td> </td><td>8</td><td>F</td><td> </td><td>E</td><td>4</td><td> </td><td>6</td><td> </td><td> </td><td>3</td><td>9</td><td> </td><td> </td><td> </td><td> </td></tr>
<tr><td> </td><td> </td><td> </td><td>7</td><td>1</td><td> </td><td> </td><td> </td><td>F</td><td>E</td><td> </td><td>D</td><td> </td><td> </td><td> </td><td>C</td></tr>
<tr><td>6</td><td> </td><td> </td><td> </td><td> </td><td>0</td><td>C</td><td> </td><td>2</td><td>4</td><td>5</td><td> </td><td> </td><td> </td><td>E</td><td>3</td></tr>
<tr><td> </td><td> </td><td> </td><td> </td><td> </td><td>C</td><td> </td><td>1</td><td>A</td><td> </td><td> </td><td> </td><td> </td><td> </td><td>2</td><td> </td></tr>
<tr><td>D</td><td> </td><td> </td><td> </td><td> </td><td> </td><td>3</td><td>9</td><td> </td><td> </td><td>B</td><td> </td><td> </td><td>1</td><td> </td><td> </td></tr>
<tr><td> </td><td>4</td><td> </td><td>6</td><td>A</td><td> </td><td> </td><td> </td><td>E</td><td>5</td><td>1</td><td> </td><td> </td><td> </td><td>3</td><td> </td></tr>
<tr><td>F</td><td> </td><td>A</td><td>C</td><td>6</td><td> </td><td>B</td><td>7</td><td> </td><td>9</td><td> </td><td> </td><td> </td><td> </td><td> </td><td>0</td></tr>
</table>

## Dodeka Sudoku
Dodeka Sudoku puzzles use the digits 0-9,A-B in a 12x12 grid. The squares
are 4x3.

<table>
<tr><td> </td><td>0</td><td> </td><td> </td><td> </td><td> </td><td>8</td><td> </td><td>7</td><td> </td><td>3</td><td> </td></tr>
<tr><td> </td><td> </td><td> </td><td>9</td><td> </td><td> </td><td> </td><td> </td><td>5</td><td>4</td><td> </td><td> </td></tr>
<tr><td> </td><td> </td><td> </td><td> </td><td>B</td><td>4</td><td> </td><td> </td><td> </td><td> </td><td>9</td><td>0</td></tr>
<tr><td> </td><td>2</td><td>5</td><td> </td><td>3</td><td> </td><td>4</td><td> </td><td> </td><td>1</td><td> </td><td> </td></tr>
<tr><td>0</td><td> </td><td>6</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>A</td><td> </td></tr>
<tr><td> </td><td> </td><td> </td><td>4</td><td>5</td><td> </td><td>9</td><td> </td><td>6</td><td> </td><td> </td><td>8</td></tr>
<tr><td>7</td><td> </td><td> </td><td>0</td><td> </td><td>2</td><td> </td><td>B</td><td>A</td><td> </td><td> </td><td> </td></tr>
<tr><td> </td><td>A</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>7</td><td> </td><td>4</td></tr>
<tr><td> </td><td> </td><td>B</td><td> </td><td> </td><td>1</td><td> </td><td>9</td><td> </td><td>8</td><td>2</td><td> </td></tr>
<tr><td>A</td><td>3</td><td> </td><td> </td><td> </td><td> </td><td>B</td><td>6</td><td> </td><td> </td><td> </td><td> </td></tr>
<tr><td> </td><td> </td><td>4</td><td>7</td><td> </td><td> </td><td> </td><td> </td><td>8</td><td> </td><td> </td><td> </td></tr>
<tr><td> </td><td>B</td><td> </td><td>5</td><td> </td><td>3</td><td> </td><td> </td><td> </td><td> </td><td>6</td><td> </td></tr>
</table>
