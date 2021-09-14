#ifndef HEX
#define HEX

#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

#endif

#include "dPath.h"


enum class hCLR: unsigned {NONE, RED, BLUE}; // color of a cell on the hex board

class hexCell
{
	public:
		hCLR color;
		int n, s;
		int nw, sw;
		int ne, se;
		
		hexCell(int N = -1, int S = -1, int NW = -1, int SW = -1, int NE = -1, int SE = -1, hCLR C = hCLR::NONE):
				color(C), n(N), s(S), nw(NW), sw(SW), ne(NE), se(SE) {}
};

class hexBoard
{
	vector< vector<hexCell> > boardCell;
	int size;
	
	public:
		hexBoard(int S = 0);
		
		hCLR getCellColor(int r, int c) { return boardCell[r][c].color; }
		hCLR getCellColor(int n) { int r{ n/size }, c{ n%size }; return boardCell[r][c].color; }
		
		void setCellColor(int r, int c, hCLR hCC) { boardCell[r][c].color = hCC; }
		void setCellColor(int n, hCLR hCC) { int r{ n/size }, c{ n%size }; boardCell[r][c].color = hCC; }
};

enum class status: unsigned {ILLEGAL = 1, CONTINUE, WINNER};

	// hexGamePlay class implements hex game engine
class hexGamePlay
{
	graph computer; // graph that tracks computer's cells on the gameboard
	graph human; // graph that tracks the human player's cells on the gameboard
	
	hexBoard gameBoard;
	
	status gameState;
	
	public:
		hexGamePlay(int B = 11): gameBoard( hexBoard{B} ), computer( graph() ), human( graph() ), gameState( status::CONTINUE ) {}
		status analyzeMove(int r, int c);
};

// computer calculates it's longest paths, and see which one's it can extend, calculates the human's and see which one's it
// can block

// after each players' move, check if longest path begins and ends on an edge cell

