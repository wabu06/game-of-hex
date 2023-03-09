#include "HexGameEngine.h"


void HexGameEngine::playHuman(pair<int, int> move)
{
	int row{move.first}, col{move.second};
	
	board.setCellColor(row, col, human.getColor(), human);
		
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
		run = false;
		currentPlayer = nullptr;
	}
	else
		currentPlayer = &computer; // human just played so computer plays next
	
	//cout << boolalpha << "win " << human.win();
}

bool HexGameEngine::isMoveLegal(pair<int, int> move)
{
	hexColors cc; // cell color
	
	int size{ board.getSize() - 1 };
	
	int row{move.first}, col{move.second};

	if( row < 0 || row > size )
	{
		ui->badMoveMsg();
		return false;
	}
		
	if( col < 0 || col > size )
	{
		ui->badMoveMsg();
		return false;
	}
		
	cc = board.getCellColor(row, col);
		
	if(cc != hexColors::NONE)
	{
		ui->badMoveMsg();
		return false;
	}

	return true;
}

void HexGameEngine::shutdown()
{
	if(!isInitialized)
		cout << "\nGame Engine Was Not Initialized" << endl;
	
	if(ui != nullptr)
		delete ui;
}

bool HexGameEngine::initialize()
{
	ui = new HexConsoleUI()
	
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

