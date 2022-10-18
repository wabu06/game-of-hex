#include "HexGameEngine.h"



void HexGameEngine::updateGame()
{
	board.setCellColor( hRow, hCol, currentPlayer->getColor() );
	
	if(currentPlayer == &computer)
		currentPlayer = &human;
	else
		currentPlayer = &computer;
	
	//board.setCellColor( hRow, hCol, human.getColor() );
	//board.setCellColor( row, col, computer.getColor() )
}

void HexGameEngine::processInput()
{
	if( currentPlayer == &computer ) // if computer is currentPlayer then do not get input from user
		return;
		
	hexColors cc; // cell color
	
	bool legal; int size{ board.getSize() - 1 };
	 
	do {
		legal = true;
		
		cout << "\nEnter your move: "; cin >> hRow >> hCol;
		
		if( hRow < 0 || hRow > size )
		{
			cout << "ILLEGAL MOVE!\n";
			legal = false;
			continue;
		}
		
		if( hCol < 0 || hCol > size )
		{
			cout << "ILLEGAL MOVE!\n";
			legal = false;
			continue;
		}
		
		cc = board.getCellColor(hRow, hCol);
		
		if(cc != hexColors::NONE)
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
			cout << "\n1) Red Player\n2) Blue Player\nEnter 1 or 2: ";
			cin >> player;
	} while( player != 1 && player != 2 );
	
	int size{ board.getSize() };
	
	if (player == 1)
	{
		human = HexPlayer(hexColors::RED, size);
		computer = HexPlayer(hexColors::BLUE, size);
		currentPlayer = &computer;
	}
	else
	{
		human = HexPlayer(hexColors::BLUE, size);
		currentPlayer = &human;
		computer = HexPlayer(hexColors::RED, size);
	}
	
	return true;
}
