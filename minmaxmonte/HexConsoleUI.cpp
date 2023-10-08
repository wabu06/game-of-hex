#define CURSE

//#include "HexGameEngine.h"


int HexConsoleUI::getHumanPlayer()
{
	struct termios oldsets, newsets;
	
	tcgetattr(STDIN_FILENO, &oldsets);
	
	newsets = oldsets;
	newsets.c_lflag &= (~ICANON);
	
	tcsetattr(STDIN_FILENO, TCSANOW, &newsets);

	int player;
			
	do
	{	cout << "\n1) Blue Player\n2) Red Player\n================>Enter 1 or 2: ";
			
		player = cin.get();
		
		cout << '\n';
				
		if( (player == 27) || (player == 32) ) {
			tcsetattr(STDIN_FILENO, TCSANOW, &oldsets);
			throw player; //return 27 + 32;
		}
	}
	while( (player != 50) && (player != 49) );
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldsets);
	
	return player - 48;
}

pair<int, int> HexConsoleUI::getHumanMove()
{
	struct termios oldsets, newsets;
	
	tcgetattr(STDIN_FILENO, &oldsets);
	
	newsets = oldsets;
	newsets.c_lflag &= (~ICANON);
	
	tcsetattr(STDIN_FILENO, TCSANOW, &newsets);
	
	int row, col;
	
	do
	{	cout << "\nEnter the row of your move: ";
			
		row = cin.get();
		
		cout << '\n';
				
		if( (row == 27) || (row == 32) ) {
			tcsetattr(STDIN_FILENO, TCSANOW, &oldsets);
			throw row; //return {27, 32};
		}
	}
	while( !isdigit( (char) row, locale("en_US.UTF8") ));
	
	do
	{	cout << "\nEnter the column of your move: ";
			
		col = cin.get();
		
		cout << '\n';
				
		if( (col == 27) || (col == 32) ) {
			tcsetattr(STDIN_FILENO, TCSANOW, &oldsets);
			throw col; //return {27, 32};
		}
	}
	while( !isdigit( (char) col, locale("en_US.UTF8") ));
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldsets);
	
	return {row - 49, col - 49};
}

void HexConsoleUI::drawHexBoard()
{
	int rows{ hge.getBoard().getSize() };
	int col, space{2}, slash;

	bool dot, back;
	
	cout << string(space, ' ');
	
	for(int r = 0; r < rows; r++)
	{
		col = 0;
		
		dot = true;
		
		while(col < rows)
		{		
			if(dot)
			{
				switch( hge.getBoard().getCellColor(r, col) )
				{
					case hexColors::BLUE:
						 cout << "B"; //cout << "\u2650";
					break;
					
					case hexColors::RED:
						 cout << "R"; //cout << "\u2648";
					break;
					
					default:
						cout << '.';
				}
				dot = false;
				col++;
			}
			else {
				cout << "---";
				dot = true;
			}
		}
		
		if( r == (rows-1) ) continue;
	
		cout << "\n";

		space++; cout << string(space, ' ');
		
		slash = 0; back = true;

		while(slash < rows)
		{
			if(back) {
				cout << "\\"; 
				back = false;
				slash++;
			}
			else {
				cout << '/';
				back = true;
			}
			cout << " ";
		}
		cout << "\n"; space++; cout << string(space, ' ');
	}
	cout << endl;
}

void HexConsoleUI::updateUI()
{
	cout << '\n'; drawHexBoard();
	
	HexPlayer* winner = hge.getWinner();
	
	if(winner != nullptr)
		cout << '\n' << winner->getID() << " Wins, Game Over\n";
}

