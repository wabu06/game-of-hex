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

void hexGamePlay::setBluePlayer(string p)
{
	bool hBlue = p == "B" || p == "b" || p == "blue" || p == "Blue"; // did the human player pick blue
	
	string blue = hBlue ? "human": "computer";
	
	bluePlayer = blue;
	gameState = state::CONTINUE;
	
	if (bluePlayer == "computer")
		cout << "computer plays first\n";
}

state hexGamePlay::updateHumanGraph(int r, int c)
{
	int s{ gameBoard.getSize() }; // game board size
	int n{ r*s + c }; // calculate node from r,c coordinates
	
	hCLR cellCLR = bluePlayer == "human" ? hCLR::BLUE : hCLR::RED;
	
	if (gameBoard.getCellColor(r, c) != hCLR::NONE)
		gameState = state::ILLEGAL;
	else
	{
		gameState = state::CONTINUE;
		
		gameBoard.setCellColor(r, c, cellCLR);
		human.addNode(n);
	}
	
	return gameState;
}

state hexGamePlay::analyzeMove(int r, int c)
{
	switch (gameState)
	{
		case state::ILLEGAL:
		break;
		
		case state::CONTINUE:
			updateHumanGraph(r, c);
		break;
			
		case state::WINNER:
				gameState = state::WINNER;
		break;
		
		case state::NOCOLORSET:
		break;
	}
	
	return gameState;
}
