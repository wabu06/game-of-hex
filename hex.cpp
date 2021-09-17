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
		// if bluePlayer was previously set do nothing
	if ( (bluePlayer=="human") || (bluePlayer=="computer") )
		return;

	bool blue = p == "B" || p == "b" || p == "blue" || p == "Blue"; // did the human player pick blue
	
	// string blue = hBlue ? "human": "computer";
	
	bluePlayer = blue ? "human": "computer";
	gameState = state::CONTINUE;
	
		// if computer is the blue player, then it gets first turn
	if (bluePlayer == "computer")
		updateComputerPlayer();
}

state hexGamePlay::updateComputerPlayer() 
{
	hCLR compCLR = bluePlayer == "computer" ? hCLR::BLUE : hCLR::RED;
	
	int s{ gameBoard.getSize() };
	
		// pick middle cell first
	if ( gameBoard.getCellColor( s/2, s/2 ) == hCLR::NONE )
	{
		gameBoard.setCellColor( s/2, s/2, compCLR);
		gameState = state::CONTINUE;
		return gameState;
	}
	
	int r, c;
	
		// find left most or top most cell that's in the computer player's graph, this will be used as the start node for find the
		// longest path in the player's graph
	if (compCLR == hCLR::RED)
	{
		for(r = 0; r < s; ++r)
		{
			for(c = 0; c < s; ++c)
			{
				if (gameBoard.getCellColor(r, c) == compCLR)
					break;
			}
			
			if (gameBoard.getCellColor(r, c) == compCLR)
				break;
		}
	}
	else
	{
		for(c = 0; c < s; ++c)
		{
			for(r = 0; r < s; ++r)
			{
				if (gameBoard.getCellColor(c, r) == compCLR)
					break;
			}
			
			if (gameBoard.getCellColor(c, r) == compCLR)
				break;
		}
	}
	
	vector<int> cNodes{ computer.getNodes() }; // nodes of computer player graph
	vector<int> maxPath;
	int max{0}, ps; // maximum path size in computer player graph
	
	dsPath mGP{ computer };
	
	int n{ r*s + c }; // calculate start node from r,c coordinates
	
	for(auto& N: cNodes)
	{
		ps = mGP.getPathSize(n,N);
		
		if (ps > max)
		{
			maxPath = mGP.getPath(n,N);
			max = ps;
		}
	}
	
	return gameState;
}

state hexGamePlay::updateHumanPlayer(int r, int c)
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
	if (gameState == state::NOCOLORSET)
		return gameState;
	
	if (gameState ==  state::WINNER)
		return gameState;
	
	if( (gameState == state::CONTINUE) || (gameState ==  state::ILLEGAL) )
	{
		updateHumanPlayer(r, c);
		
		if (gameState == state::ILLEGAL)
			return gameState;
		else
		{
			if (gameState == state::WINNER)
				return gameState;
			else
			{
				updateComputerPlayer();
				return gameState;
			}
		}
	}
	
	return gameState;	
}
