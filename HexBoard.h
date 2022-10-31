#pragma once


#include<vector>
#include<array>

#include "hex.h"

class hexCell
{
	public:
		hexColors color;
		int left, right; // neighbors on the left & right sides of a cell
		int upperL, lowerL; // neighbors at the upper & lower left sides of a cell
		int upperR, lowerR; // neighbors at the upper & lower right sides of a cell
		
		hexCell(int L, int R, int UL, int LL, int UR, int LR, hexColors C = hexColors::NONE):
				left(L), right(R), upperL(UL), lowerL(LL), upperR(UR), lowerR(LR), color(C) {}
};

class HexBoard
{
	vector< vector<hexCell> > boardCell;
	int size;
	
	public:
		HexBoard(int S = 0);
		
		int getSize() { return size; }
		
		hexColors getCellColor(int r, int c) { return boardCell[r][c].color; }
		hexColors getCellColor(int n) { int r{ n/size }, c{ n%size }; return boardCell[r][c].color; }
		
		void setCellColor(int r, int c, hexColors hCC) { boardCell[r][c].color = hCC; }
		void setCellColor(int n, hexColors hCC) { int r{ n/size }, c{ n%size }; boardCell[r][c].color = hCC; }
		
		int getRightNeighbor(int n) { int r{ n/size }, c{ n%size }; return boardCell[r][c].right; }
		int getLeftNeighbor(int n) { int r{ n/size }, c{ n%size }; return boardCell[r][c].left; }
		int getUpperLeftNeighbor(int n) { int r{ n/size }, c{ n%size }; return boardCell[r][c].upperL; }
		int getLowerLeftNeighbor(int n) { int r{ n/size }, c{ n%size }; return boardCell[r][c].lowerL; }
		int getUpperRightNeighbor(int n) { int r{ n/size }, c{ n%size }; return boardCell[r][c].upperR; }
		int getLowerRightNeighbor(int n) { int r{ n/size }, c{ n%size }; return boardCell[r][c].lowerR; }
		
		vector<int> getCellNeighbors(int cell, int fn, bool cw);
};
