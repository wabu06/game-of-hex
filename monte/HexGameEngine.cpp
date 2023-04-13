#include "HexGameEngine.h"


void HexGameEngine::playHuman()
{
	// pair<int, int> move;

	bool legal;
	
	int row, col;
			
	do
	{	tie(row, col) = ui->getHumanMove();
			
		if(done)
		{
			currentPlayer = nullptr;
			return; // end game if human choose to quit instead of entering a move
		}
			
		legal = isMoveLegal(row, col);
	}
	while(!legal);

	//int row{move.first}, col{move.second};
	
	board.setCellColor( row, col, human.getColor() ); //, human);
		
			// create edge between cell neighbors that are the same color
	int cell{ row*board.getSize() + col };
		
	vector<int> neighbors = board.getCellNeighbors(cell);
		
	for(auto& N: neighbors)
	{
		if( board.getCellColor(N) == human.getColor() )
			human.connectCells(cell, N);
	}

	ui->displayMsg("Human selects cell (" + to_string(row+1) + ", " + to_string(col+1) + ")");
	
	if( human.win() )
	{
		winner = &human;
		done = true;
		currentPlayer = nullptr;
	}
	else
		currentPlayer = &computer; // human just played so computer plays next
}

bool HexGameEngine::isMoveLegal(int row, int col)
{
	hexColors cc; // cell color
	
	int size{ board.getSize() - 1 };
	
	//int row{move.first}, col{move.second};

	if( row < 0 || row > size )
	{
		ui->displayMsg("ILLEGAL MOVE!");
		return false;
	}
		
	if( col < 0 || col > size )
	{
		ui->displayMsg("ILLEGAL MOVE!");
		return false;
	}
		
	cc = board.getCellColor(row, col);
		
	if(cc != hexColors::NONE)
	{
		ui->displayMsg("ILLEGAL MOVE!");
		return false;
	}

	return true;
}

#define CONCUR 0

bool HexGameEngine::initialize()
{
#if CONCUR
	ui = new HexConsoleUI(this); // user interface
#else
	ui = new HexCurseUI(this);
#endif
	
	int player = ui->getHumanPlayer();
	
	int size{ board.getSize() };
	
	if (player == 1)
	{
		human = HexPlayer(hexColors::BLUE, size);
		currentPlayer = &human;
		computer = HexPlayer(hexColors::RED, size);
	}
	else
	{
		human = HexPlayer(hexColors::RED, size);
		computer = HexPlayer(hexColors::BLUE, size);
		currentPlayer = &computer;
	}
	
	isInitialized = true;
	
	return isInitialized;
}

