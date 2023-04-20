#pragma once


#include<vector>
#include<array>
//#include<iostream>

#include "HexPlayer.h"


enum class sides: unsigned {L, R, UL, LL, UR, LR};

class HexBoard
{
	int size;
	vector< vector<hexColors> > boardCell;
	
	public:
		HexBoard(int S = 0): size(S), boardCell( vector< vector<hexColors> >( size, vector<hexColors>(size, hexColors::NONE) ) ) {}
		
		HexBoard(const HexBoard& brd) : size(brd.size), boardCell(brd.boardCell) {}
		
		HexBoard& operator=(const HexBoard& brd) {
			this->size = brd.size;
			this->boardCell = brd.boardCell;
			
			return *this;
		}
		
		/*HexBoard operator=(HexBoard&& B) {
			this->size = B.size;
			this->boardCell = B.boardCell;
			
			return *this;
		}*/

		int getSize() {
			return size;
		}
		
		hexColors getCellColor(int r, int c) {
			return boardCell[r][c];
		}
		
		hexColors getCellColor(int n) {
			int r{ n/size }, c{ n%size };
			return boardCell[r][c];
		}
		
		void setCellColor(int r, int c, hexColors hCC) {
			boardCell[r][c] = hCC;
		}
		
		void setCellColor(int n, hexColors hCC) {
			int r{ n/size }, c{ n%size };
			boardCell[r][c] = hCC;
		}
		
		vector<int> getCellNeighbors(int cell)
		{
			vector<int> neighbors = vector<int>();
	
			array<sides, 6> SIDES = {sides::R, sides::LR, sides::LL, sides::L, sides::UL, sides::UR};
	
			for(auto& s: SIDES)
			{
				auto n = getCellNeighbor(cell, s);
				
				if(n > -1)
					neighbors.push_back(n);
			}
	
			return neighbors;
		}
		
		vector<int> getBlueNeighbors(int cell);
		
		vector<int> getRedNeighbors(int cell);
		
		int getCellNeighbor(int n, sides S);
};
