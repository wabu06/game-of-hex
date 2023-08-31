#pragma once


#define HEX

#include<vector>
#include<array>
//#include<iostream>

#include "HexGameEngine.h"


using namespace std;

enum class sides: unsigned {L, R, UL, LL, UR, LR};

class HexBoard
{
	int size, nones;

	vector< vector<hexColors> > boardCell;
	
	public:
		HexBoard(int S = 0): size(S), nones(S*S), boardCell( vector< vector<hexColors> >( size, vector<hexColors>(size, hexColors::NONE) ) ) {}
		
		HexBoard(const HexBoard& brd) : size(brd.size), nones(brd.nones), boardCell(brd.boardCell) {}
		
		HexBoard& operator=(const HexBoard& brd) {
			this->size = brd.size;
			this->boardCell = brd.boardCell;
			this->nones = brd.nones;
			
			return *this;
		}
		
		HexBoard& operator=(HexBoard&& brd) noexcept // move assignment operator
		{
			if(this == &brd)
				return *this;

			this->size = brd.size;
			this->boardCell = brd.boardCell;
			this->nones = brd.nones;
			
			return *this;
		}
		
		vector< vector<hexColors> > getCells() {
			return boardCell;
		}

		int getSize() {
			return size;
		}
		
		int getNoneCount() {
			return nones;
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
			nones--;
		}
		
		void setCellColor(int n, hexColors hCC) {
			int r{ n/size }, c{ n%size };
			boardCell[r][c] = hCC;
			nones--;
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
