#include "hex.h"



hexBoard::hexBoard(int S)
{
	size = S;
	boardCell = vector< vector<hexCell> >(size);
			
	int r{0};
			
	for(auto& C: boardCell)
	{
		for(int i = 0; i < size; ++i)
		{
			C.push_back( hexCell( r*S + i+1, r*S + i-1, (r+1) * S + i, (r+1) * S + i + 1, (r-1) * S + i, (r-1) * S + i - 1) );
		}
				
		r++;
	}
}

status hexGamePlay::analyzeMove(int r, int c)
{
	if (gameBoard.getCellColor(r, c) != hCLR::NONE)
		return status::ILLEGAL;
	else
		return status::CONTINUE;
}
