////////////////////////////////////////////////////////////////////////////////
//
//  Dancing Links - Implementation of Donald Knuth's DLX algorithm for
//  Sudoku puzzles.
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
//  Class ResultListener has just a method for receiving a result..
//
///////////////////////////////////////////////////////////////////////////////

class ResultListener
{
public:
    virtual void onResult(int[PUZZLE_SIDE][PUZZLE_SIDE]){};
};
