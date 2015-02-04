
G++    := g++
SRC    := Sudoku.cpp DancingLinks.cpp
CFLAGS := -g

all:	Sudoku.exe

Sudoku.exe:	$(SRC)

%.exe:	%.cpp
	$(G++) -o $@ $(CFLAGS) $^
