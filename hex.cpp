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
	
	int s{ gameBoard.getSize() }; int n{ (s/2)*s + (s/2) };
	
		// pick middle cell first
	if ( gameBoard.getCellColor( s/2, s/2 ) == hCLR::NONE )
	{
		gameBoard.setCellColor( s/2, s/2, compCLR);
		
		computer.addNode(n);
		
		gameState = state::CONTINUE; return gameState;
	}
	
	vector<int> cNodes{ computer.getNodes() }; // the nodes of computer player graph
	
	vector<int> maxPath; int maxPS{0}, ps; // maximum path size in computer player graph
	
		// instance of class that implements Dijkstra's Algorithm, used to find the maximum path in computer player graph	
	dsPath mGP{ computer };
	
	for(auto& ON: cNodes)
	{
		for(auto& IN: cNodes)
		{
			ps = mGP.getPathSize(ON,IN);
			
			if (ps > maxPS)
			{
				maxPath = mGP.getPath(ON,IN);
				maxPS = ps;
			}
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
