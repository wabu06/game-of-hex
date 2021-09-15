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

status hexGamePlay::updateHumanGraph(int r, int c)
{
	int s{ gameBoard.getSize() }; // game board size
	int n{ r*s + c }; // calculate node from r,c coordinates
	
	if (gameBoard.getCellColor(r, c) != hCLR::NONE)
		gameState = status::ILLEGAL;
	else
	{
		gameState = status::CONTINUE;
		
		gameBoard.setCellColor(r, c, hCLR::BLUE);
		human.addNode(n);
	}
	
	return gameState;
}

status hexGamePlay::analyzeMove(int r, int c)
{
	switch (gameState)
	{
		case status::ILLEGAL: case status::CONTINUE:
			updateHumanGraph(r, c);
		break;
			
		case status::WINNER:
				gameState = status::WINNER;
			break;
	}
	
	return gameState;
}
