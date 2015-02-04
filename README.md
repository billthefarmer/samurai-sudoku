# Samurai Sudoku
Saumurai, Hexadoku, Dodeka and Sudoku using Donald Knuth's Dancing Links algorithm

Implementations in plain vanilla C++ of Donald Knuth's Dancing Links algorith for
Samurai Sudoku, Hexadoku, Dodeka Sudoku and Sudoku. I investigated the use of
smart pointers for the links, but decided as it works just fine with raw pointers
to leave it. I have made no attempt to track and release the use of memory by the
algorith as the programs just exit and return it all anyway.

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
