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

vector<int> HexBoard::getBlueNeighbors(int cell, bool top)
{
	vector<int> neighbors = vector<int>();
	
	array<sides, 6> topSide = {sides::UL, sides::UR, sides::R, sides::LR, sides::LL, sides::L};
	array<sides, 6> bottomSide = {sides::LR, sides::LL, sides::R, sides::UR, sides::UL, sides::L};
			
	if(top)
	{
		for(auto& s: topSide)
		{
			auto n = getCellNeighbor(cell, s);
				
			if(n > -1)
				neighbors.push_back(n);
		}
	}
	else
	{
		for(auto& s: bottomSide)
		{
			auto n = getCellNeighbor(cell, s);
				
			if(n > -1)
				neighbors.push_back(n);
		}
	}
			
	return neighbors;
}

vector<int> HexBoard::getRedNeighbors(int cell, bool right)
{
	vector<int> neighbors = vector<int>();
	
	array<sides, 6> rightSide = {sides::R, sides::UR, sides::LR, sides::LL, sides::L, sides::UL};
	array<sides, 6> leftSide = {sides::L, sides::UL, sides::LL, sides::R, sides::LR, sides::UR};
	
	if(right)
	{		
		for(auto& s: rightSide)
		{
			auto n = getCellNeighbor(cell, s);
				
			if(n > -1)
				neighbors.push_back(n);
		}
	}
	else
	{
		for(auto& s: leftSide)
		{
			auto n = getCellNeighbor(cell, s);
				
			if(n > -1)
				neighbors.push_back(n);
		}
	}
			
	return neighbors;
}

