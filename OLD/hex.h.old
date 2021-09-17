#ifndef HEX
#define HEX

#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>

using namespace std;

#endif

#include "dPath.h"


enum class hCLR: unsigned {NONE, RED, BLUE}; // color of a cell on the hex board

	// cells on the hex game board
class hexCell
{
	public:
		hCLR color;
		int left, right; // neighbors on the left & right sides of a cell
		int upperL, lowerL; // neighbors at the upper & lower left sides of a cell
		int upperR, lowerR; // neighbors at the upper & lower right sides of a cell
		
		hexCell(int L = -1, int R = -1, int UL = -1, int LL = -1, int UR = -1, int LR = -1, hCLR C = hCLR::NONE):
				left(L), right(R), upperL(UL), lowerL(LL), upperR(UR), lowerR(LR), color(C) {}
};

class hexBoard
{
	vector< vector<hexCell> > boardCell;
	int size;
	
	public:
		hexBoard(int S = 0);
		
		int getSize() { return size; }
		
		hCLR getCellColor(int r, int c) { return boardCell[r][c].color; }
		hCLR getCellColor(int n) { int r{ n/size }, c{ n%size }; return boardCell[r][c].color; }
		
		void setCellColor(int r, int c, hCLR hCC) { boardCell[r][c].color = hCC; }
		void setCellColor(int n, hCLR hCC) { int r{ n/size }, c{ n%size }; boardCell[r][c].color = hCC; }
};

enum class state: unsigned {NOCOLORSET, ILLEGAL, CONTINUE, WINNER};

	// hexGamePlay class implements hex game engine
class hexGamePlay
{
	graph computer; // graph that tracks computer's cells on the gameboard
	graph human; // graph that tracks the human player's cells on the gameboard 
	
	string bluePlayer;
	
	hexBoard gameBoard;
	
	state gameState;
	
	state updateHumanPlayer(int r, int c);
	state updateComputerPlayer();
	
	public:
		hexGamePlay(int B = 11):
			gameBoard( hexBoard{B} ), computer( graph() ), human( graph() ), bluePlayer("none"), gameState( state::NOCOLORSET ) {}
				
		state analyzeMove(int r, int c);
		
		void setBluePlayer(string p);
		
		state getGameState() { return gameState; }
};

// computer calculates it's longest paths, and see which one's it can extend, calculates the human's and see which one's it
// can block

// after each players' move, check if longest path begins and ends on an edge cell

