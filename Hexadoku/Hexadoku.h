////////////////////////////////////////////////////////////////////////////////
//
//  Hexadoku - Hexadoku solver.
//
//  Copyright (C) 2015	Bill Farmer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  Bill Farmer	 william j farmer [at] yahoo [dot] co [dot] uk.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
//  Define constants for the dimensions of the puzzle.
//
///////////////////////////////////////////////////////////////////////////////

enum
    {PUZZLE_SIDE = 16,
     SQUARE_SIDE = 4,
     PUZZLE_SIZE = 256,
     COLUMN_SIZE = 1024};

#include "ResultListener.h"

///////////////////////////////////////////////////////////////////////////////
//
//   Class Hexadoku defines some puzzles from the Times or Sunday Times
//   and solves them.
//
///////////////////////////////////////////////////////////////////////////////

class Hexadoku: public ResultListener
{
public:
    Hexadoku(int){};
    ~Hexadoku(){};

    void solve(int[PUZZLE_SIDE][PUZZLE_SIDE]);
    void onResult(int[PUZZLE_SIDE][PUZZLE_SIDE]);
};
