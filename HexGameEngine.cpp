#include "HexGameEngine.h"



void HexGameEngine::updateGame()
{
	board.setCellColor( hRow, hCol, human.getColor() )
	
	//board.setCellColor( row, col, computer.getColor() )
}

void HexGameEngine::processInput()
{
	hexColors cc; // cell color
	
	bool legal; int size = board.getSize();
	 
	do {
		legal = true;
		
		cout << "Enter your move: "; cin >> hRow >> hCol;
		
		if( hRow < 0 || hRow > size-1 )
		{
			cout << "ILLEGAL MOVE!\n";
			legal = false;
			continue;
		}
		
		if( hCol < 0 || hCol > size-1 )
		{
			cout << "ILLEGAL MOVE!\n";
			legal = false;
			continue;
		}
		
		cc = board.getCellColor(hRow, hCol);
		
		if(cc != hexColors.NONE)
		{
			cout << "ILLEGAL MOVE!\n";
			legal = false;
		}
		
	} while(!legal);
}

void HexGameEngine::generateOutput()
{
	char ans; 
	cout << "\nContinue game?(y/n) "; cin >> ans;
	
	if (ans != 'y') run = false;
}

void HexGameEngine::runLoop()
{
	while(run)
	{
		processInput(); // check for legality of a move
		updateGame(); // update player graphs and gameBoard
		generateOutput();
	}
}

void HexGameEngine::shutdown() {}

bool HexGameEngine::initialize()
{	
	int player;
	
	do {
			cout << "1) Red Player or 2) Blue Player, Enter 1 or 2: ";
			cin >> player;
	} while( player != 1 && player != 2 );
	
	if (player == 1)
	{
		human = HexPlayer(hexColors.RED);
		computer = HexPlayer(hexColors.Blue);
	}
	else
	{
		human = HexPlayer(hexColors.BLUE);
		computer = HexPlayer(hexColors.RED);
	}
	
	return true;
}
