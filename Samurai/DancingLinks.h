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
//  Class DancingLinks implements the Dancing Links algorithm adapted
//  for Samurai Sudoku puzzles.
//
///////////////////////////////////////////////////////////////////////////////

class Node;
class Column;
class ResultListener;

class DancingLinks
{
public:
    ResultListener *listener;
    int stats[PUZZLE_SIZE];
    int index;
    Column *h;
    Node *o[PUZZLE_SIZE];

    DancingLinks(int[PUZZLE_SIDE][PUZZLE_SIDE]);
    ~DancingLinks(){};

    void report(int[]);
    void solve();
    void search(int);
    void setListener(ResultListener *);
};

///////////////////////////////////////////////////////////////////////////////
//
//  Class Node has four links: left, right, up, down, which reference
//  adjacent nodes, a link which references the column and a row
//  number.
//
///////////////////////////////////////////////////////////////////////////////

class Node
{
public:
    Node *l;
    Node *r;
    Node *u;
    Node *d;
    Column *c;
    int n;

    Node(Column *, int);
    ~Node(){};

    void remove();
    void add(Node *);
};


///////////////////////////////////////////////////////////////////////////////
//
//  Class Column inherits the links from the Node class and has a column size.
//
///////////////////////////////////////////////////////////////////////////////

class Column: public Node
{
public:
    int s;

    Column(Column *, int);
    ~Column(){};

    void cover();
    void uncover();

    void add(Column *);
    void add(Node *);
};
