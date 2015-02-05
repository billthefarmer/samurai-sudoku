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

#include <cstdlib>
#include <climits>

#include "Samurai.h"
#include "DancingLinks.h"
#include "ResultListener.h"

///////////////////////////////////////////////////////////////////////////////
//
//   Declare an array which defines which squares are in which puzzle,
//   including those in two puzzles, and those that aren't in any
//   puzzle, an array which defines which puzzle row a samurai row is
//   in, and an array which defines which puzzle column a samurai
//   column is in.
//
///////////////////////////////////////////////////////////////////////////////

static const int SAMURAI_SQUARE[][2] = 
    {{0, -1}, {0, -1}, {0, -1}, {-1,-1}, {1, -1}, {1, -1}, {1, -1},
     {0, -1}, {0, -1}, {0, -1}, {-1,-1}, {1, -1}, {1, -1}, {1, -1},
     {0, -1}, {0, -1}, {0, 2},  {2, -1}, {1, 2},  {1, -1}, {1, -1},
     {-1,-1}, {-1,-1}, {2, -1}, {2, -1}, {2, -1}, {-1,-1}, {-1,-1},
     {3, -1}, {3, -1}, {2, 3},  {2, -1}, {2, 4},  {4, -1}, {4, -1},
     {3, -1}, {3, -1}, {3, -1},{-1,-1},  {4, -1}, {4, -1}, {4, -1},
     {3, -1}, {3, -1}, {3, -1},{-1,-1},  {4, -1}, {4, -1}, {4, -1}};

static const int SUDOKU_ROW[][PUZZLE_SIDE] =
    {{ 0, 1, 2, 3, 4, 5, 6, 7, 8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
     { 0, 1, 2, 3, 4, 5, 6, 7, 8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
     {-1,-1,-1,-1,-1,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8,-1,-1,-1,-1,-1,-1},
     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8},
     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8}};

static const int SUDOKU_COLUMN[][PUZZLE_SIDE] =
    {{ 0, 1, 2, 3, 4, 5, 6, 7, 8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8},
     {-1,-1,-1,-1,-1,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8,-1,-1,-1,-1,-1,-1},
     { 0, 1, 2, 3, 4, 5, 6, 7, 8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8}};


///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Class DancingLinks implements the Dancing Links algorithm adapted
//  for Samurai Sudoku puzzles.
//
///////////////////////////////////////////////////////////////////////////////

// Create a column head and add 1692 (21 x 21 = 441 slots + 5 puzzles
// x 9 rows x 9 digits = 405 + 5 puzzles x 9 columns x 9 digits = 405
// + 49 slots x 9 digits = 441) columns. Empty columns will be
// removed. 3645 (9 rows x 9 columns x 9 digits x 5 puzzles) rows of
// nodes are added to the columns. Those rows corresponding to slots
// in one puzzle will have four nodes, those overlapping two puzzles
// will have six nodes. If a row is part of the puzzle it is removed
// from the matrix and added to the solution.

DancingLinks::DancingLinks(const int p[PUZZLE_SIDE][PUZZLE_SIDE])
{
    // Clear the index

    index = 0;

    // Clear the stats

    for (int i = 0; i < PUZZLE_SIZE; i++)
	stats[i] = 0;

    // Column row head.

    h = new Column(NULL, 0);
    Column *m[COLUMN_SIZE];

    // Create the row of columns.

    for (int i = 0; i < COLUMN_SIZE; i++)
	m[i] = new Column(h, 0);

    // List of rows that are part of the solution.

    Node *l[PUZZLE_SIZE];
    int i = 0;

    // For each samurai (big) row, column and possible digit.

    for (int r = 0; r < PUZZLE_SIDE; r++)
    {
	for (int c = 0; c < PUZZLE_SIDE; c++)
	{
	    for (int d = 0; d < SUDOKU_SIDE; d++)
	    {
		// Calculate row number for possible
		// move in samurai (big) puzzle.

		int k = 1 + (r * PUZZLE_SIDE * SUDOKU_SIDE) +
		    (c * SUDOKU_SIDE) + d;

		// See what samurai (big) square we're in.

		int s = (c / 3) + ((r / 3) * 7);

		// If the slot is in a puzzle create a row of
		// nodes.

		if (SAMURAI_SQUARE[s][0] > -1)
		{
		    // Create a node for the slot.

		    Node *n = new Node(m[(r * PUZZLE_SIDE) + c], k);

		    // For each puzzle that this slot is in...

		    for (int j = 0; j < 2; j++)
		    {
			// Find which puzzle the slot is in.

			int pz = SAMURAI_SQUARE[s][j];

			if (pz > -1)
			{
			    // Find the puzzle row and column.

			    int pr = SUDOKU_ROW[pz][r];
			    int pc = SUDOKU_COLUMN[pz][c];

			    // Add a node for the puzzle, row and
			    // digit.

			    n->add(new Node(m[PUZZLE_SIZE +
					      (pz * SUDOKU_SIZE) +
					      (pr * SUDOKU_SIDE) + d], k));

			    // Add a node for the puzzle, column
			    // and digit.

			    n->add(new Node(m[PUZZLE_SIZE + 405 +
					      (pz * SUDOKU_SIZE) +
					      (pc * SUDOKU_SIDE) + d], k));
			}
		    }

		    // Add a node for the samurai (big) square
		    // and digit.

		    n->add(new Node(m[PUZZLE_SIZE + 405 + 405 +
				     (s * SUDOKU_SIDE) + d], k));

		    // If this row is in the puzzle, add it to the
		    // list.

		    if (p[c][r] == (d + 1))
			l[i++] = n;
		}
	    }
	}
    }

    // There will be empty columns corresponding to the unused
    // slots in the samurai (big) puzzle. Remove the empty
    // columns.

    for (Column *c = (Column *) h->r; c != h; c = (Column *) c->r)
	if (c->s == 0)
	    c->cover();

    // Remove the rows in the list and add them to the output.

    for (int j = 0; j < i; j++)
    {
	l[j]->remove();
	o[index++] = l[j];
    }
}

// Rearrange the output to match the puzzle.

void DancingLinks::report(int o[PUZZLE_SIZE])
{
    // Create an array for the result.

    int a[PUZZLE_SIDE][PUZZLE_SIDE];

    // Convert the row number back to row, column, digit.

    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
	int v = o[i];

	int d = v % SUDOKU_SIDE;
	int c = (v / SUDOKU_SIDE) % PUZZLE_SIDE;
	int r = (v / (PUZZLE_SIDE * SUDOKU_SIDE)) % PUZZLE_SIDE;

	a[c][r] = d + 1;
    }

    // Report the result.

    listener->onResult(a);

    // Create an array for the stats

    int s[PUZZLE_SIDE][PUZZLE_SIDE];

    for (int i = 0; i < PUZZLE_SIDE; i++)
	s[i / PUZZLE_SIDE][i % PUZZLE_SIDE] = stats[i];

    // Report stats.

    listener->onResult(s);
}

// Start the search process.

void DancingLinks::solve()
{
    search(index);
}

// This is the procedure search(k) from the Dancing Links
// algorithm with an added feature to report only one
// solution.

void DancingLinks::search(int k)
{
    // If a result has already been found, return.

    // if (stop)
    // 	return;

    // If there are no more columns, report the result.

    if (h->r == h)
    {
	int a[k];

	// Extract the row numbers.

	for (int i = 0; i < k; i++)
	    a[i] = o[i]->n - 1;

	// Report the result and set the stop flag.

	report(a);
	// stop = true;
    }

    // Else find the shortest column and cover it.

    else
    {
	Column *c = NULL;
	int s = INT_MAX;

	// Increment stats;

	stats[k]++;

	// Find the shortest column.

	for (Column *j = (Column *) h->r; j != h; j = (Column *) j->r)
	    if (s > j->s)
	    {
		c = j;
		s = j->s;
	    }

	// Cover it.

	c->cover();

	// For each row in the column...

	for (Node *r = c->d; r != c; r = r->d)
	{
	    // Skip this if a result has been found.

	    // if (stop)
	    // 	break;

	    // Save the row in the output array.

	    o[k] = r;

	    // For each node in this row, cover it's column.

	    for (Node *j = r->r; j != r; j = j->r)
		j->c->cover();

	    // Recurse with k + 1.

	    search(k + 1);

	    // For each node in this row, uncover it's column.

	    for (Node *j = r->l; j != r; j = j->l)
		j->c->uncover();
	}

	// Uncover the column.

	c->uncover();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Class Node has four links: left, right, up, down, which reference
//  adjacent nodes, a link which references the column and a row
//  number.
//
///////////////////////////////////////////////////////////////////////////////

// Create a self referencing node.

Node::Node(Column *c, int n)
{
    this->l = this;
    this->r = this;

    this->u = this;
    this->d = this;

    // Column and row number.

    this->c = c;
    this->n = n;

    // If the column isn't NULL, add this node to it.

    if (c != NULL)
	c->add(this);
}
 
// Remove a row of nodes.

void Node::remove()
{
    Node *n = this;

    // Cover this node's column and move on to the next right.

    do
    {
	n->c->cover();
	n = n->r;
    }

    // While we haven't got back to this node.

    while (n != this);
}

// Add a node to the left of this node.

void Node::add(Node *n)
{
    n->l = this->l;
    n->r = this;

    this->l->r = n;
    this->l = n;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Class Column inherits the links from the Node class and has a column size.
//
///////////////////////////////////////////////////////////////////////////////

// Create a self referencing column using the Node constructor.

Column::Column(Column *c, int n): Node(c, n)
{
    if (c != NULL)
	c->add(this);

    s = 0;
}

// This is the procedure cover(c) from the Dancing Links
// algorithm.

void Column::cover()
{
    // Cover this column.

    r->l = l;
    l->r = r;

    // For all the rows in this column going down...

    for (Node *i = d; i != this; i = i->d)
    {
	// For all the nodes in this row except this one,
	// going right...

	for (Node *j = i->r; j != i; j = j->r)
	{
	    // Cover this row.

	    j->u->d = j->d;
	    j->d->u = j->u;

	    // Adjust the column size.

	    j->c->s--;
	}
    }
}

// This is the procedure uncover(c) from the Dancing Links
// algorithm.

void Column::uncover()
{
    // For all the rows in this column going up...

    for (Node *i = u; i != this; i = i->u)
    {
	// For all the nodes in this row except this one,
	// going left...

	for (Node *j = i->l; j != i; j = j->l)
	{
	    // Uncover this row.

	    j->u->d = j;
	    j->d->u = j;

	    // Adjust the column size.

	    j->c->s++;
	}
    }

    // Uncover this column.

    r->l = this;
    l->r = this;
}

// Add a column to the left of this column.

void Column::add(Column *c)
{
    c->l = this->l;
    c->r = this;

    this->l->r = c;
    this->l = c;
}

// Add a node to the end of this column.

void Column::add(Node *n)
{
    n->u = this->u;
    n->d = this;

    this->u->d = n;
    this->u = n;

    // Increment the column size.

    s++;
}
