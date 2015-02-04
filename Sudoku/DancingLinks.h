///////////////////////////////////////////////////////////////////////////////
//
//   DancingLinks.h  1.0  26 May 2006
//
//   Dancing Links - solve puzzles using Dancing Links algorithm by
//   Donald Knuth. See academic paper 'Dancing Links', Donald
//   E. Knuth, Stanford University.
//
//   Copyright (C) 2006 Bill Farmer
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
//  Class DancingLinks implements the Dancing Links algorithm adapted
//  for Sudoku puzzles.
//
///////////////////////////////////////////////////////////////////////////////

class Node;
class Column;
class ResultListener;

class DancingLinks
{
public:
    ResultListener *listener;
    unsigned int stats[PUZZLE_SIZE];
    int index;
    Column *h;
    Node *o[PUZZLE_SIZE];

    DancingLinks(int[PUZZLE_SIDE][PUZZLE_SIDE]);
    ~DancingLinks(){};

    void report(unsigned int[]);
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
