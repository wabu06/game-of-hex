#include "HexGameEngine.h"


void HexGameEngine::playHuman()
{
	bool legal;
	
	int row, col;
			
	do
	{	try {
			tie(row, col) = exe->getHumanMove();
		}
		catch(int exp)
		{
			done = true;
			return;
		}

		legal = isMoveLegal(row, col);
		
		if(!legal)
			exe->displayMsg("ILLEGAL MOVE!");
	}
	while(!legal);

	board.setCellColor( row, col, human.getColor() );
		
			// create edge between cell neighbors that are the same color
	int cell{ row*board.getSize() + col };
		
	vector<int> neighbors = board.getCellNeighbors(cell);
		
	for(auto& N: neighbors)
	{
		if( board.getCellColor(N) == human.getColor() )
			human.connectCells(cell, N);
	}

	exe->displayMsg("Human selects cell (" + to_string(row+1) + ", " + to_string(col+1) + ")");
	
	if( human.win() )
	{
		winner = &human;
		done = true;
	}
}

bool HexGameEngine::isMoveLegal(int row, int col)
{
	int size{ board.getSize() - 1 };
	
	bool inRange = (row >= 0) && (row <= size);
	
	inRange = (col >= 0) && (col <= size) && inRange;

	if(!inRange)
		return inRange;
	else
	{
		hexColors cc = board.getCellColor(row, col); // cell color

		return inRange && (cc == hexColors::NONE);
	}
}

bool HexGameEngine::initialize()
{
	int player;
	
	try {
		player = exe->getHumanPlayer();
	}
	catch(int exp) {
		done = true;
		isInitialized = false;
		return isInitialized;
	}
	
	isInitialized = true;
	done = false;

	//generateMove = &HexGameEngine::genMonteMove;
	generateMove = &HexGameEngine::genMiniMaxMove;

	int size{ board.getSize() };
	
	if (player == 1)
	{
		human = HexPlayer(hexColors::BLUE, size, "Human");
		computer = HexPlayer(hexColors::RED, size, "Computer");
		//playCurrentPlayer = &HexGameEngine::playHuman;
	}
	else
	{
		human = HexPlayer(hexColors::RED, size, "Human");
		computer = HexPlayer(hexColors::BLUE, size, "Computer");
		//playCurrentPlayer = &HexGameEngine::playComputer;
	}

	return isInitialized;
}

