////////////////////////////////////////////////////////////////////////////////
//
//  Dodeka - Dodeka Sudoku solver.
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

#include <iostream>

#include "Dodeka.h"
#include "DancingLinks.h"
#include "ResultListener.h"

int main()
{
    // Create an instance.

    Dodeka dodeka(0);

    // Define some puzzles.

    int puzzle1[PUZZLE_SIDE][PUZZLE_SIDE] =
	{{-1, 0,-1,-1,-1,-1, 8,-1, 7,-1, 3,-1},
	 {-1,-1,-1, 9,-1,-1,-1,-1, 5, 4,-1,-1},
	 {-1,-1,-1,-1,11, 4,-1,-1,-1,-1, 9, 0},
	 {-1, 2, 5,-1, 3,-1, 4,-1,-1, 1,-1,-1},
	 { 0,-1, 6,-1,-1,-1,-1,-1,-1,-1,10,-1},
	 {-1,-1,-1, 4, 5,-1, 9,-1, 6,-1,-1, 8},
	 { 7,-1,-1, 0,-1, 2,-1,11,10,-1,-1,-1},
	 {-1,10,-1,-1,-1,-1,-1,-1,-1, 7,-1, 4},
	 {-1,-1,11,-1,-1, 1,-1, 9,-1, 8, 2,-1},
	 {10, 3,-1,-1,-1,-1,11, 6,-1,-1,-1,-1},
	 {-1,-1, 4, 7,-1,-1,-1,-1, 8,-1,-1,-1},
	 {-1,11,-1, 5,-1, 3,-1,-1,-1,-1, 6,-1}};

    int puzzle2[PUZZLE_SIDE][PUZZLE_SIDE] =
	{{ 3,-1,-1,-1,-1,-1, 2,-1,-1,10,-1, 1},
	 {-1,-1,-1,11,-1,-1, 0,-1, 9, 5,-1,-1},
	 {-1,-1,-1,-1, 1,-1, 9,-1,-1,-1, 8, 6},
	 {-1, 5,-1,-1,-1, 6,-1,11, 1, 4,-1,-1},
	 {-1, 0,10,-1,-1,-1,-1, 8,-1,-1,-1, 9},
	 {11,-1,-1,-1,-1,-1, 4,-1,-1,-1, 7, 0},
	 {10,11,-1,-1,-1, 9,-1,-1,-1,-1,-1, 2},
	 { 9,-1,-1,-1, 7,-1,-1,-1,-1, 8, 5,-1},
	 {-1,-1, 7, 5, 3,-1,11,-1,-1,-1, 9,-1},
	 { 7, 3,-1,-1,-1, 2,-1, 0,-1,-1,-1,-1},
	 {-1,-1, 6,10,-1,11,-1,-1, 0,-1,-1,-1},
	 { 2,-1, 1,-1,-1, 7,-1,-1,-1,-1,-1, 4}};

    int puzzle3[PUZZLE_SIDE][PUZZLE_SIDE] =
	{{-1, 3, 8,-1,-1, 4,11,-1,-1,10, 2,-1},
	 {-1,-1,-1,10,-1,-1,-1,-1, 7,-1,-1,-1},
	 {-1, 9,-1,-1,10,-1,-1, 7,-1,-1, 6,-1},
	 {-1, 7,-1, 3, 4, 6, 1, 9,11,-1, 0,-1},
	 {-1,-1, 9,-1, 5,-1,-1,10,-1, 7,-1,-1},
	 { 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 6},
	 { 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8},
	 {-1,-1,10,-1, 9,-1,-1, 1,-1, 4,-1,-1},
	 {-1, 4,-1, 7, 2, 5, 0, 8, 9,-1, 1,-1},
	 {-1, 8,-1,-1, 6,-1,-1, 4,-1,-1,10,-1},
	 {-1,-1,-1, 0,-1,-1,-1,-1, 2,-1,-1,-1},
	 {-1,10, 6,-1,-1, 9, 3,-1,-1, 5, 4,-1}};

    int puzzle4[PUZZLE_SIDE][PUZZLE_SIDE] =
	{{-1, 8,-1,-1, 9,-1,-1,-1,-1, 5, 7,-1},
	 {-1,-1,11,-1,-1,-1,-1,-1,-1,-1,-1, 0},
	 {-1, 4, 1, 5,-1, 2, 8,-1,-1,-1,-1,-1},
	 {10,-1,-1,-1,-1,-1,-1, 6, 3,-1,-1,-1},
	 { 2,-1, 5,-1,11,10,-1, 4,-1, 9,-1,-1},
	 {-1, 7, 4,-1, 1, 9,-1,-1, 6,-1,-1,-1},
	 {-1,-1,-1, 2,-1,-1, 9, 1,-1, 4, 5,-1},
	 {-1,-1, 9,-1, 4,-1,10, 5,-1, 1,-1, 2},
	 {-1,-1,-1, 4, 6,-1,-1,-1,-1,-1,-1,10},
	 {-1,-1,-1,-1,-1,11, 0,-1, 7, 2, 4,-1},
	 { 1,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1},
	 {-1, 3, 8,-1,-1,-1,-1,10,-1,-1, 9,-1}};

    // Solve them.

    dodeka.solve(puzzle1);
    dodeka.solve(puzzle2);
    dodeka.solve(puzzle3);
    dodeka.solve(puzzle4);
}

///////////////////////////////////////////////////////////////////////////////
//
//   Class Dodeka defines some puzzles from the Times or Sunday Times
//   and solves them.
//
///////////////////////////////////////////////////////////////////////////////

// Solve a puzzle.

void Dodeka::solve(int puzzle[PUZZLE_SIDE][PUZZLE_SIDE])
{
    // Create a new Dancing Links.

    DancingLinks dl(puzzle);

    // Set the listener

    dl.setListener(this);

    // Solve the puzzle.

    dl.solve();
}

// Print the solution.

void Dodeka::onResult(int solution[PUZZLE_SIDE][PUZZLE_SIDE])
{
    for (int r = 0; r < PUZZLE_SIDE; r++)
    {
	for (int c = 0; c < PUZZLE_SIDE; c++)
	    std::cout << std::uppercase << std::hex << solution[r][c] << " ";

	std::cout << "\n";
    }

    std::cout << "-----------------------\n";
}
