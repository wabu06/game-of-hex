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
	
	//array<sides, 6> sideAR = {sides::LR, sides::UL, sides::LL, sides::UR, sides::L, sides::R};
	array<sides, 6> middle = {sides::LR, sides::UL, sides::LL, sides::UR, sides::L, sides::R};
	array<sides, 6> lower = {sides::LR, sides::LL, sides::UL, sides::UR, sides::L, sides::R}; //, sides::UL, sides::UR};
	array<sides, 6> upper = {sides::UL, sides::UR, sides::LR, sides::LL, sides::L, sides::R};
	
	auto crow = size/2; // center row
	auto row = cell/size;
	
	array<sides, 6> sideAR;
	
	if(row > crow)
		sideAR = lower;
	else
	{
		if(row < crow)
			sideAR = upper;
		else
			sideAR = middle;
	}
	
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
	
	array<sides, 6> sideAR; // = {sides::L, sides::R, sides::UL, sides::UR, sides::LL, sides::LR};
	array<sides, 6> left = {sides::L, sides::UL, sides::LL, sides::R, sides::LR, sides::UR};
	array<sides, 6> middle = {sides::L, sides::R, sides::UL, sides::UR, sides::LL, sides::LR};
	array<sides, 6> right = {sides::R, sides::UR, sides::LR, sides::L, sides::UL, sides::LL};
	
	auto ccol = size%2; // center column
	auto col = cell%size;
	
	if(col > ccol)
		sideAR = right;
	else
	{
		if(col < ccol)
			sideAR = left;
		else
			sideAR = middle;
	}
	
	for(auto& s: sideAR)
	{
		auto n = getCellNeighbor(cell, s);
				
		if(n > -1)
			neighbors.push_back(n);
	}
			
	return neighbors;
}

