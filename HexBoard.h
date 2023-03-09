#pragma once


#include<vector>
#include<array>
//#include<iostream>

#define _HEX

#include "HexPlayer.h"


enum class sides: unsigned {L, R, UL, LL, UR, LR};

class HexBoard
{
	int size;
	vector< vector<hexColors> > boardCell;
	
	public:
		HexBoard(int S = 0): size(S), boardCell( vector< vector<hexColors> >( size, vector<hexColors>(size, hexColors::NONE) ) ) {}

		int getSize() { return size; }
		
		hexColors getCellColor(int r, int c) { return boardCell[r][c]; }
		
		hexColors getCellColor(int n)
		{
			int r{ n/size }, c{ n%size };
			return boardCell[r][c];
		}
		
		void setCellColor(int r, int c, hexColors hCC, HexPlayer& player)
		{
			boardCell[r][c] = hCC;
			player.addCell( r*size + c );
		}
		
		void setCellColor(int n, hexColors hCC, HexPlayer& player)
		{
			int r{ n/size }, c{ n%size };
			boardCell[r][c] = hCC;
			player.addCell(n);
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
