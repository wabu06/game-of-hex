#include "HexGameEngine.h"


void HexGameEngine::playHuman()
{
	pair<int, int> move;

	bool legal;
			
	do
	{	move = ui->getHumanMove(this);
			
		if(done)
		{
			currentPlayer = nullptr;
			return; // end game if human choose to quit instead of entering a move
		}
			
		legal = isMoveLegal(move);
	}
	while(!legal);

	int row{move.first}, col{move.second};
	
	board.setCellColor( row, col, human.getColor() ); //, human);
		
			// create edge between cell neighbors that are the same color
	int cell{ row*board.getSize() + col };
		
	vector<int> neighbors = board.getCellNeighbors(cell);
		
	for(auto& N: neighbors)
	{
		if( board.getCellColor(N) == human.getColor() )
			human.connectCells(cell, N);
	}
	
	if( human.win() )
	{
		winner = &human;
		done = true;
		currentPlayer = nullptr;
	}
	else
		currentPlayer = &computer; // human just played so computer plays next
}

bool HexGameEngine::isMoveLegal(pair<int, int> move)
{
	hexColors cc; // cell color
	
	int size{ board.getSize() - 1 };
	
	int row{move.first}, col{move.second};

	if( row < 0 || row > size )
	{
		ui->displayMsg("ILLEGAL MOVE!\n");
		return false;
	}
		
	if( col < 0 || col > size )
	{
		ui->displayMsg("ILLEGAL MOVE!\n");
		return false;
	}
		
	cc = board.getCellColor(row, col);
		
	if(cc != hexColors::NONE)
	{
		ui->displayMsg("ILLEGAL MOVE!\n");
		return false;
	}

	return true;
}

bool HexGameEngine::initialize()
{
	ui = new HexConsoleUI(); // user interface
	
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

