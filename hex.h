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

class hexBoard
{
	vector< vector<hCLR> > boardCell;
	int size;
	
	public:
		hexBoard(int S = 0);
		
		int getSize() { return size; }
		
		hCLR getCellColor(int r, int c) { return boardCell[r][c]; }
		hCLR getCellColor(int n) { int r{ n/size }, c{ n%size }; return boardCell[r][c]; }
		
		void setCellColor(int r, int c, hCLR hCC) { boardCell[r][c] = hCC; }
		void setCellColor(int n, hCLR hCC) { int r{ n/size }, c{ n%size }; boardCell[r][c] = hCC; }
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
	
	void addNeighborEdges(int r, int c, hCLR color);
	
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

