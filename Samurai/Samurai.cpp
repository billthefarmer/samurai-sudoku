////////////////////////////////////////////////////////////////////////////////
//
//  Samurai - Samurai Sudoku solver.
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

#include "Samurai.h"
#include "DancingLinks.h"
#include "ResultListener.h"

///////////////////////////////////////////////////////////////////////////////
//
//   Samurai Sudoku puzzles are made up of five overlapping puzzles
//   like this:
//
//      +---+---+---+   +---+---+---+
//      |   |   |   |   |   |   |   |
//      +---+---+---+   +---+---+---+
//      |   | 1 |   |   |   | 2 |   |
//      +---+---+---+---+---+---+---+
//      |   |   | A |   | B |   |   |
//      +---+---+---+---+---+---+---+
//              |   | 3 |   |
//      +---+---+---+---+---+---+---+
//      |   |   | C |   | D |   |   |
//      +---+---+---+---+---+---+---+
//      |   | 4 |   |   |   | 5 |   |
//      +---+---+---+   +---+---+---+
//      |   |   |   |   |   |   |   |
//      +---+---+---+   +---+---+---+
//
//   The slots in the four squares labelled A, B, C, D that overlap
//   the centre and outer four puzzles must be solved for both
//   puzzles.
//
///////////////////////////////////////////////////////////////////////////////

int main()
{
    // Create an instance.

    Samurai samurai(0);

    // Define some puzzles.

    static int puzzle1[PUZZLE_SIDE][PUZZLE_SIDE] =
	{{0,0,0,0,0,5,0,0,0, 0,0,0, 0,0,0,0,2,0,6,0,0},
	 {0,0,7,3,0,0,9,0,0, 0,0,0, 0,0,0,0,0,3,0,0,5},
	 {0,5,0,0,9,0,0,6,3, 0,0,0, 0,0,8,0,0,0,0,4,0},

	 {0,8,0,0,7,3,0,0,0, 0,0,0, 0,4,0,3,0,0,8,0,0},
	 {0,0,6,2,0,0,8,0,0, 0,0,0, 7,0,0,0,9,0,5,0,0},
	 {4,0,0,5,0,0,0,9,0, 0,0,0, 0,0,0,0,5,0,0,7,0},

	 {0,3,0,0,5,0, 0,0,0,7,0,0,0,0,0, 0,0,1,0,0,0},
	 {0,0,8,0,0,9, 0,3,0,0,4,9,6,8,0, 4,0,0,2,0,0},
	 {0,0,9,0,0,0, 0,0,2,0,0,0,0,0,5, 0,0,0,0,8,0},

	 {0,0,0,0,0,0, 9,0,0,6,0,0,0,5,0, 0,0,0,0,0,0},
	 {0,0,0,0,0,0, 0,6,0,0,0,0,2,0,0, 0,0,0,0,0,0},
	 {0,0,0,0,0,0, 0,5,0,0,0,0,7,0,0, 0,0,0,0,0,0},

	 {0,0,0,0,3,0, 0,4,0,0,1,5,8,0,0, 0,0,6,0,0,0},
	 {0,0,0,9,0,0, 0,2,0,3,0,0,0,9,0, 0,0,4,0,0,6},
	 {0,0,2,0,0,0, 0,0,1,0,0,0,0,0,0, 0,0,8,0,2,0},

	 {0,0,0,3,0,0,0,5,0, 0,0,0, 0,0,0,0,4,0,3,0,0},
	 {7,0,0,0,1,9,0,0,0, 0,0,0, 0,0,0,5,0,0,7,0,0},
	 {0,6,0,0,0,0,2,0,0, 0,0,0, 3,5,6,0,0,0,0,8,0},

	 {3,0,0,2,9,0,0,7,0, 0,0,0, 0,0,0,2,6,0,0,0,1},
	 {0,0,5,0,0,4,0,0,8, 0,0,0, 0,0,3,0,0,5,0,0,0},
	 {0,8,0,0,0,0,0,0,0, 0,0,0, 0,7,0,0,0,0,9,0,0}};

    static int puzzle2[PUZZLE_SIDE][PUZZLE_SIDE] =
	{{4,9,7,0,0,0,0,0,0, 0,0,0, 0,1,8,0,0,0,6,7,9},
	 {8,0,0,0,0,0,0,9,7, 0,0,0, 0,4,0,8,0,0,0,0,3},
	 {1,0,0,0,0,0,6,0,8, 0,0,0, 0,0,2,0,9,0,0,0,4},

	 {0,0,0,3,0,5,0,7,0, 0,0,0, 0,0,0,2,0,6,0,0,0},
	 {0,0,5,0,4,0,1,0,0, 0,0,0, 0,0,0,0,5,0,0,0,0},
	 {0,8,0,2,0,6,0,0,0, 0,0,0, 0,0,0,7,0,9,0,0,0},

	 {7,0,3,0,0,0, 0,0,5,0,0,0,7,0,0, 0,2,0,1,0,0},
	 {2,6,0,0,0,0, 0,0,4,0,0,0,1,0,0, 0,0,7,0,2,0},
	 {0,0,0,0,0,0, 7,1,6,0,5,0,4,2,9,0, 0,0,7,3,0},

	 {0,0,0,0,0,0, 0,0,0,1,0,5,0,0,0, 0,0,0,0,0,0},
	 {0,0,0,0,0,0, 0,0,3,0,0,0,2,0,0, 0,0,0,0,0,0},
	 {0,0,0,0,0,0, 0,0,0,4,0,9,0,0,0, 0,0,0,0,0,0},

	 {0,9,7,0,0,0, 3,4,8,0,1,0,9,7,6, 0,0,0,0,0,0},
	 {0,3,0,7,0,0, 0,0,9,0,0,0,5,0,0, 0,0,0,0,9,2},
	 {0,0,4,0,9,0, 0,0,7,0,0,0,3,0,0, 0,0,0,1,0,8},

	 {0,0,0,8,0,3,0,0,0, 0,0,0, 0,0,0,3,0,9,0,8,0},
	 {0,0,0,0,6,0,0,0,0, 0,0,0, 0,0,3,0,8,0,4,0,0},
	 {0,0,0,5,0,7,0,0,0, 0,0,0, 0,2,0,4,0,1,0,0,0},

	 {7,0,0,0,5,0,2,0,0, 0,0,0, 7,0,5,0,0,0,0,0,6},
	 {5,0,0,0,0,9,0,8,0, 0,0,0, 2,8,0,0,0,0,0,0,9},
	 {4,6,9,0,0,0,5,7,0, 0,0,0, 0,0,0,0,0,0,2,1,5}};

    // Solve them.

    samurai.solve(puzzle1);
    samurai.solve(puzzle2);
}

///////////////////////////////////////////////////////////////////////////////
//
//   Class Samurai defines some puzzles from the UK Saturday Times and
//   solves them.
//
///////////////////////////////////////////////////////////////////////////////

// Solve a puzzle.

void Samurai::solve(int puzzle[PUZZLE_SIDE][PUZZLE_SIDE])
{
    // Create a new Dancing Links.

    DancingLinks dl(puzzle);

    // Print the puzzle for checking.

    onResult(puzzle);

    // Solve the puzzle.

    dl.solve();
}

// Print the solution.

void Samurai::onResult(int solution[PUZZLE_SIDE][PUZZLE_SIDE])
{
    for (int r = 0; r < PUZZLE_SIDE; r++)
    {
	for (int c = 0; c < PUZZLE_SIDE; c++)
	    if (solution[r][c] > 0)
		std::cout << solution[r][c] << " ";

	    else
		std::cout << ". ";

	std::cout << "\n";
    }

    std::cout << "-----------------------------------------\n";
}
