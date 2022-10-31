#include "HexBoard.h"

HexBoard::HexBoard(int S)
{
	size = S;
	boardCell = vector< vector<hexCell> >(size);
	
	int L, R, UR, LR, UL, LL;
			
	for(int r = 0; r < size; ++r)
	{
		for(int c = 0; c < size; ++c)
		{	
				// left neighbor
			if( (c-1) >= 0 )
				L = r*S + c-1;
			else
				L = -1;
				
				// right neighbor
			if( (c+1) < S ) //if( (c+1) < (S-1) )
				R = r*S + c+1;
			else
				R = -1;
			
					// upper right neighbor
			if( ( (r-1) >= 0) && ( (c+1) < S ) ) //if( ( (r-1) >= 0) && ( (c+1) < (S-1) ) )
				UR = (r-1)*S + c+1;
			else
				UR = -1;

				// lower right neighbor
			if( (r+1) < S  ) //if( ( (r+1) < (S-1) ) )
				LR = (r+1)*S + c;
			else
				LR = -1;

				// upper left neighbor
			if( (r-1) >= 0 )
				UL = (r-1)*S + c;
			else
				UL = -1;

				// lower left neighbor
			if( ( (r+1) < S ) && ( (c-1) >= 0 ) ) //if( ((r+1) < (S-1)) && ((c-1) >= 0) )
				LL = (r+1)*S + c-1;
			else
				LL = -1;
				
			boardCell[r].push_back( hexCell(L, R, UL, LL, UR, LR) );
		}
	}
}

vector<int> HexBoard::getCellNeighbors(int cell, int fn, bool cw)
{
	vector<int> neighbors = vector<int>();
	
	array<string, 6> ns = {"R", "LR", "LL", "L", "UL", "UR"};
	
	for(int i = 0; i < 6; ++i)
	{
		if ( ns[fn] == "R" )
			neighbors.push_back( getRightNeighbor(cell) );
		
		if ( ns[fn] == "LR" )
			neighbors.push_back( getLowerRightNeighbor(cell) );
		
		if ( ns[fn] == "LL" )
			neighbors.push_back( getLowerLeftNeighbor(cell) );
		
		if ( ns[fn] == "L" )
			neighbors.push_back( getLeftNeighbor(cell) );
		
		if ( ns[fn] == "UL" )
			neighbors.push_back( getUpperLeftNeighbor(cell) );
		
		if ( ns[fn] == "UR" )
			neighbors.push_back( getUpperRightNeighbor(cell) );
		
		if (cw) // clock wise or counter clock wise
		{
			if (fn == 5)
				fn = 0;
			else
				++fn;
		}
		else
		{
			if (fn == 0)
				fn = 5;
			else
				--fn;
		}
	}
	
	return neighbors;
}

