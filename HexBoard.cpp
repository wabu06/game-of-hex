#include "HexBoard.h"


int HexBoard::getCellNeighbor(int cell, sides S)
{
	auto r{cell/size}, c{cell%size}; int n;
	
	switch(S)
	{
		case sides::L:
			n = (c-1) >= 0 ? r*size + c-1: -1; // left neighbor
		break;
		
		case sides::R: 
			n = (c+1) < size ? r*size + c+1: -1; // right neighbor
		break;
		
		case sides::UR:
			n = ( (r-1) >= 0) && ( (c+1) < size ) ? (r-1)*size + c+1: -1; // upper right neighbor
		break;
		
		case sides::LR:
			n = (r+1) < size ? (r+1)*size + c: -1; // lower right neighbor
		break;
		
		case sides::UL:
			n = (r-1) >= 0 ? (r-1)*size + c: -1; // upper left neighbor
		break;
		
		case sides::LL:
			n = ( (r+1) < size ) && ( (c-1) >= 0 ) ? (r+1)*size + c-1: -1; // lower left neighbor
		break;	
	}
	
	return n;
}

vector<int> HexBoard::getBlueNeighbors(int cell)
{
	vector<int> neighbors = vector<int>();
	
	array<sides, 6> sideAR = {sides::LR, sides::UL, sides::LL, sides::UR, sides::L, sides::R};
	
	for(auto& s: sideAR)
	{
		auto n = getCellNeighbor(cell, s);
				
		if(n > -1)
			neighbors.push_back(n);
	}
			
	return neighbors;
}

vector<int> HexBoard::getRedNeighbors(int cell)
{
	vector<int> neighbors = vector<int>();
	
	array<sides, 6> sideAR = {sides::L, sides::R, sides::UL, sides::UR, sides::LL, sides::LR};
		
	for(auto& s: sideAR)
	{
		auto n = getCellNeighbor(cell, s);
				
		if(n > -1)
			neighbors.push_back(n);
	}
			
	return neighbors;
}

