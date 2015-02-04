///////////////////////////////////////////////////////////////////////////////
//
//   Samurai.h  1.0  24 June 2006
//
//   Samurai - solve Samurai Sudoku puzzles from the UK Saturday Times
//   using Dancing Links algorithm by Donald Knuth. See academic paper
//   'Dancing Links', Donald E. Knuth, Stanford University.
//
//   Copyright (C) 2006 Bill Farmer
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
//  Define constants for the dimensions of the puzzle.
//
///////////////////////////////////////////////////////////////////////////////

enum
    {PUZZLE_SIDE = 21,
     PUZZLE_SIZE = 441,
     SUDOKU_SIDE = 9,
     SUDOKU_SIZE = 81,
     SQUARE_SIDE = 3,
     COLUMN_SIZE = 1692};

#include "ResultListener.h"

///////////////////////////////////////////////////////////////////////////////
//
//   Class Samurai defines some puzzles from the UK Saturday Times and
//   solves them.
//
///////////////////////////////////////////////////////////////////////////////

class Samurai: public ResultListener
{
public:
    Samurai(int){};
    ~Samurai(){};

    void solve(int[PUZZLE_SIDE][PUZZLE_SIDE]);
    void onResult( int[PUZZLE_SIDE][PUZZLE_SIDE]);
};
