#include "hex.h"



hexBoard::hexBoard(int S)
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
			if( (c+1) < (S-1) )
				R = r*S + c+1;
			else
				R = -1;
			
					// upper right neighbor
			if( ( (r-1) >= 0) && ( (c+1) < (S-1) ) )
				UR = (r-1)*S + c+1;
			else
				UR = -1;

				// lower right neighbor
			if( ( (r+1) < (S-1) ) )
				LR = (r+1)*S + c;
			else
				LR = -1;

				// upper left neighbor
			if( (r-1) >= 0 )
				UL = (r-1)*S + c;
			else
				UL = -1;

				// lower left
			if( ((r+1) < (S-1)) && ((c-1) >= 0) )
				LL = (r+1)*S + c-1;
			else
				LL = -1;
				
			boardCell[r].push_back( hexCell(L, R, UL, LL, UR, LR) );
		}
	}
}

void hexGamePlay::setBluePlayer(string p)
{
		// if bluePlayer was previously set do nothing
	if ( (bluePlayer=="human") || (bluePlayer=="computer") )
		return;

	bool blue = p == "B" || p == "b" || p == "blue" || p == "Blue"; // did the human player pick blue
	
	bluePlayer = blue ? "human": "computer";
	gameState = state::CONTINUE;
	
		// if computer is the blue player, then it gets first turn
	if (bluePlayer == "computer")
		updateComputerPlayer();
}

void hexGamePlay::addNeighborEdges(int r, int c, hCLR color)
{
	int s{ gameBoard.getSize() }; // game board size
	
	int n{ r*s + c }; // calculate node from r,c coordinates
	
			// if right neighbor has same color add edge
	if( (c+1) < (s-1) )
	{
		if (gameBoard.getCellColor(r, c+1) == color)
			human.addEdge( n, r*s + c+1, 1 );
	}

		// if left neighbor has same color add edge
	if( (c-1) >= 0 )
	{
		if (gameBoard.getCellColor(r, c-1) == color)
			human.addEdge( n, r*s + c-1, 1 );
	}

		// if upper right neighbor has same color add edge
	if( ((r-1) >= 0) && ((c+1) < (s-1)) )
	{
		if (gameBoard.getCellColor(r-1, c+1) == color)
			human.addEdge( n, (r-1)*s + c+1, 1 );
	}

		// if lower right neighbor has same color add edge
	if( ( (r+1) < (s-1)) )
	{
		if (gameBoard.getCellColor(r+1, c) == color)
			human.addEdge( n, (r+1)*s + c, 1 );
	}

		// if upper left neighbor has same color add edge
	if( (r-1) >= 0 )
	{
		if (gameBoard.getCellColor(r-1, c) == color)
			human.addEdge( n, (r-1)*s + c, 1 );
	}

		// if lower left neighbor has same color add edge
	if( ((r+1) < (s-1)) && ((c-1) >= 0) )
	{
		if (gameBoard.getCellColor(r+1, c-1) == color)
			human.addEdge( n, (r+1)*s + c-1, 1 );
	}
}

state hexGamePlay::updateComputerPlayer() 
{
	hCLR compCLR = bluePlayer == "computer" ? hCLR::BLUE : hCLR::RED;
	
	int s{ gameBoard.getSize() }; int n{ (s/2)*s + (s/2) };
	
		// pick middle cell first, if not already chosen
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
	
	int maxRC{ s-1 }; // maximum row or column
	
	if( (r < 0) || (r > maxRC) )
	{
		gameState = state::ILLEGAL;
		return gameState;
	}
	
	if( (c < 0) || (c > maxRC) )
	{
		gameState = state::ILLEGAL;
		return gameState;
	}
	
	int n{ r*s + c }; // calculate node from r,c coordinates
	
	hCLR cellCLR = bluePlayer == "human" ? hCLR::BLUE : hCLR::RED;
	
	if (gameBoard.getCellColor(r, c) != hCLR::NONE)
	{
		gameState = state::ILLEGAL;
		return gameState;
	}

	gameState = state::CONTINUE;
		
	gameBoard.setCellColor(r, c, cellCLR);
	human.addNode(n);
		
	addNeighborEdges(r, c, cellCLR);
		
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
