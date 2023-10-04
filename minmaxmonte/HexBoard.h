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
	int trc, brc, lcc, rcc; // top row, bottom row, left column, & right column color counts

	vector< vector<hexColors> > boardCell;
	
	public:
		HexBoard(int S = 0): size(S), nones(S*S), trc(S), brc(S), lcc(S), rcc(S),
							 boardCell( vector< vector<hexColors> >( size, vector<hexColors>(size, hexColors::NONE) ) ) {}
		
		HexBoard(const HexBoard& brd) : size(brd.size), nones(brd.nones), trc(brd.trc), brc(brd.brc), lcc(brd.lcc), rcc(brd.rcc),
										boardCell(brd.boardCell) {}
		
		HexBoard& operator=(const HexBoard& brd)
		{
			this->size = brd.size;
			this->boardCell = brd.boardCell;
			this->nones = brd.nones;
			
			this->trc = brd.trc;
			this->brc = brd.brc;
			this->lcc = brd.lcc;
			this->rcc = brd.rcc;
			
			return *this;
		}
		
		HexBoard& operator=(const HexBoard&& brd) noexcept // move assignment operator
		{
			if(this == &brd)
				return *this;

			this->size = brd.size;
			this->boardCell = brd.boardCell;
			this->nones = brd.nones;
			
			this->trc = brd.trc;
			this->brc = brd.brc;
			this->lcc = brd.lcc;
			this->rcc = brd.rcc;
			
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
		
		void setCellColor(int r, int c, hexColors hCC)
		{
			boardCell[r][c] = hCC;
			nones--;
			
			if(r-1 < 0)
				trc--;
			
			if(r+1 > size-1)
				brc--;
			
			if(c-1 < 0)
				lcc--;
			
			if(c+1 > size-1)
				rcc--;
		}
		
		void setCellColor(int n, hexColors hCC)
		{
			int r{ n/size }, c{ n%size };
			
			boardCell[r][c] = hCC;
			nones--;
			
			if(r-1 < 0)
				trc--;
			
			if(r+1 > size-1)
				brc--;
			
			if(c-1 < 0)
				lcc--;
			
			if(c+1 > size-1)
				rcc--;
				
		}
		
		bool gotDraw() {
			return (trc <= 0) && (brc <= 0) && (lcc <= 0) && (rcc <= 0);
		}
		
		tuple<int, int, int, int> getColorCounts() {
			return {trc, brc, lcc, rcc};
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
		
		//vector<int> getBlueNeighbors(int cell);
		
		//vector<int> getRedNeighbors(int cell);
		
		int getCellNeighbor(int n, sides S);
};
