////////////////////////////////////////////////////////////////////////////////
//
//  Sudoku - Sudoku solver.
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

#include "Sudoku.h"
#include "DancingLinks.h"
#include "ResultListener.h"

int main()
{
    // Create an instance.

    Sudoku sudoku(0);

    // Define some puzzles.

    int puzzle1[PUZZLE_SIDE][PUZZLE_SIDE] =
	{{0, 0, 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 4, 9, 0, 7, 1, 0, 0},
	 {0, 7, 8, 5, 0, 1, 6, 4, 0},
	 {9, 0, 0, 4, 0, 8, 0, 0, 3},
	 {0, 0, 0, 0, 0, 0, 0, 0, 0},
	 {5, 0, 0, 6, 0, 9, 0, 0, 7},
	 {0, 3, 9, 1, 0, 4, 5, 2, 0},
	 {0, 0, 1, 7, 0, 5, 3, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int puzzle2[PUZZLE_SIDE][PUZZLE_SIDE] =
	{{0, 0, 0, 9, 0, 0, 8, 5, 0},
	 {0, 0, 3, 0, 0, 8, 0, 0, 0},
	 {0, 2, 0, 0, 0, 4, 1, 3, 0},
	 {0, 0, 0, 0, 5, 9, 0, 7, 0},
	 {7, 0, 0, 0, 0, 0, 0, 0, 6},
	 {0, 4, 0, 2, 7, 0, 0, 0, 0},
	 {0, 5, 2, 8, 0, 0, 0, 6, 0},
	 {0, 0, 0, 1, 0, 0, 2, 0, 0},
	 {0, 9, 4, 0, 0, 2, 0, 0, 0}};

    int puzzle3[PUZZLE_SIDE][PUZZLE_SIDE] =
	{{0, 0, 3, 0, 0, 8, 0, 0, 6},
	 {0, 0, 0, 4, 6, 0, 0, 0, 0},
	 {0, 0, 0, 1, 0, 0, 5, 9, 0},
	 {0, 9, 8, 0, 0, 0, 6, 4, 0},
	 {0, 0, 0, 0, 7, 0, 0, 0, 0},
	 {0, 1, 7, 0, 0, 0, 9, 5, 0},
	 {0, 2, 4, 0, 0, 1, 0, 0, 0},
	 {0, 0, 0, 0, 4, 6, 0, 0, 0},
	 {6, 0, 0, 5, 0, 0, 8, 0, 0}};

    int puzzle4[PUZZLE_SIDE][PUZZLE_SIDE] =
	{{6, 0, 0, 9, 0, 0, 2, 0, 4},
	 {0, 0, 8, 0, 1, 0, 0, 6, 0},
	 {0, 0, 0, 6, 0, 0, 5, 0, 0},
	 {0, 3, 0, 0, 0, 0, 0, 4, 5},
	 {0, 0, 6, 0, 0, 0, 9, 0, 0},
	 {4, 8, 0, 0, 0, 0, 0, 3, 0},
	 {0, 0, 1, 0, 0, 5, 0, 0, 0},
	 {0, 7, 0, 0, 2, 0, 1, 0, 0},
	 {8, 0, 2, 0, 0, 7, 0, 0, 9}};

    // Solve them.

    sudoku.solve(puzzle1);
    sudoku.solve(puzzle2);
    sudoku.solve(puzzle3);
    sudoku.solve(puzzle4);
}

///////////////////////////////////////////////////////////////////////////////
//
//   Class Sudoku defines some puzzles from the Times or Sunday Times
//   and solves them.
//
///////////////////////////////////////////////////////////////////////////////

// Solve a puzzle.

void Sudoku::solve(int puzzle[PUZZLE_SIDE][PUZZLE_SIDE])
{
    // Create a new Dancing Links.

    DancingLinks dl(puzzle);

    // Set the listener

    dl.setListener(this);

    // Solve the puzzle.

    dl.solve();
}

// Print the solution.

void Sudoku::onResult(int solution[PUZZLE_SIDE][PUZZLE_SIDE])
{
    for (int r = 0; r < PUZZLE_SIDE; r++)
    {
	for (int c = 0; c < PUZZLE_SIDE; c++)
	    std::cout << solution[r][c] << " ";

	std::cout << "\n";
    }

    std::cout << "-----------------\n";
}
