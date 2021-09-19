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

vector<int> hexBoard::getCellNeighbors(int cell, int fn, bool cw)
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

void hexGamePlay::addNeighborEdges(int r, int c, hCLR color, string player)
{
	int s{ gameBoard.getSize() }; // game board size
	
	int n{ r*s + c }; // calculate node from r,c coordinates
	
			// if right neighbor has same color add edge
	if( (c+1) < (s-1) )
	{
		if (gameBoard.getCellColor(r, c+1) == color)
		{
			if( player == "human")
				human.addEdge( n, r*s + c+1, 1 );
			else
				computer.addEdge( n, r*s + c+1, 1 );
		}
	}

		// if left neighbor has same color add edge
	if( (c-1) >= 0 )
	{
		if (gameBoard.getCellColor(r, c-1) == color)
		{
			if( player == "human")
				human.addEdge( n, r*s + c-1, 1 );
			else
				computer.addEdge( n, r*s + c-1, 1 );
		}
	}

		// if upper right neighbor has same color add edge
	if( ((r-1) >= 0) && ((c+1) < (s-1)) )
	{
		if (gameBoard.getCellColor(r-1, c+1) == color)
		{
			if( player == "human")
				human.addEdge( n, (r-1)*s + c+1, 1 );
			else
				computer.addEdge( n, (r-1)*s + c+1, 1 );
		}
	}

		// if lower right neighbor has same color add edge
	if( ( (r+1) < (s-1)) )
	{
		if (gameBoard.getCellColor(r+1, c) == color)
		{
			if( player == "human")
				human.addEdge( n, (r+1)*s + c, 1 );
			else
				computer.addEdge( n, (r+1)*s + c, 1 );
		}
	}

		// if upper left neighbor has same color add edge
	if( (r-1) >= 0 )
	{
		if (gameBoard.getCellColor(r-1, c) == color)
		{
			if( player == "human")
				human.addEdge( n, (r-1)*s + c, 1 );
			else
				computer.addEdge( n, (r-1)*s + c, 1 );	
		}
	}

		// if lower left neighbor has same color add edge
	if( ((r+1) < (s-1)) && ((c-1) >= 0) )
	{
		if (gameBoard.getCellColor(r+1, c-1) == color)
		{
			if( player == "human")
				human.addEdge( n, (r+1)*s + c-1, 1 );
			else
				computer.addEdge( n, (r+1)*s + c-1, 1 );
		}
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
		
		if( gameBoard.getCellColor( gameBoard.getRightNeighbor(n) ) == compCLR)
			computer.addEdge( n, gameBoard.getRightNeighbor(n), 1 );
		
		if( gameBoard.getCellColor( gameBoard.getLeftNeighbor(n) ) == compCLR)
			computer.addEdge( n, gameBoard.getLeftNeighbor(n), 1 );
		
		if( gameBoard.getCellColor( gameBoard.getUpperRightNeighbor(n) ) == compCLR)
			computer.addEdge( n, gameBoard.getUpperRightNeighbor(n), 1 );
		
		if( gameBoard.getCellColor( gameBoard.getLowerRightNeighbor(n) ) == compCLR)
			computer.addEdge( n, gameBoard.getLowerRightNeighbor(n), 1 );
		
		if( gameBoard.getCellColor( gameBoard.getUpperLeftNeighbor(n) ) == compCLR)
			computer.addEdge( n, gameBoard.getUpperLeftNeighbor(n), 1 );
		
		if( gameBoard.getCellColor( gameBoard.getLowerLeftNeighbor(n) ) == compCLR)
			computer.addEdge( n, gameBoard.getLowerLeftNeighbor(n), 1 );
		
		gameState = state::CONTINUE; return gameState;
	}
	
	vector<int> cNodes{ computer.getNodes() }; // the nodes of computer player graph
	
	vector<int> maxPath; int maxPS{0}, ps; // maximum path size in computer player graph
	
		// instance of class that implements Dijkstra's Algorithm, used to find the maximum path in computer player graph	
	dsPath mGP{ computer };
	
		// find maximum path
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
	
		// find best way to expand maximum path
	for(auto& NC: gameBoard.getCellNeighbors( maxPath.back(), 0, true ) )
	{
		if (NC >= 0)
		{
			if( gameBoard.getCellColor(NC) == hCLR::NONE )
			{
				gameBoard.setCellColor(NC, compCLR);
				computer.addNode(NC);
				computer.addEdge( maxPath.back(), NC, 1 );
				
				gameState = state::CONTINUE;
				break; // what if all neighbors are already colored
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
		
	addNeighborEdges(r, c, cellCLR, "human");
		
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
