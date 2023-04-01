//#include "HexConsoleUI.h"

#include "HexGameEngine.h"


pair<int, int> HexConsoleUI::getHumanMove(HexGameEngine* hge)
{
	string input; pair<int, int> position;

	while(true)
	{
		cout << "\nEnter selection for your move, <h> for help, or <q> to quit: "; getline(cin, input);
		
		auto toLowerCase = [](char& c){ c = tolower( c, locale("en_US.UTF8") ); };
	
		for_each(input.begin(), input.end(), toLowerCase);
		
		bool allAlpha = all_of(input.begin(), input.end(), [](char& c) { return isalpha( c, locale("en_US.UTF8") ); });
		
		if(allAlpha)
		{
			if( (input == "q") || (input == "quit") || (input == "exit") || (input == "end") )
			{
				hge->setCurrentPlayer(nullptr);
				hge->endGame();
				position.first = position.second = static_cast<unsigned int>('q') * static_cast<unsigned int>('Q');
				break;
			}
			
			if( (input == "h") || (input == "help") )
			{
				cout << "\nIf for example you want to select the cell at row 5, & column 2, simply enter 52.\n";
				cout << "Or if you wanted to select the cell at row 7, & column 11, enter 0711.\n";
				continue;
			}
		}
		
		bool allDigits = all_of(input.begin(), input.end(), [](char c) { return isdigit( c, locale("en_US.UTF8") ); });
		
		if(allDigits)
		{
			int number = stoi(input, nullptr);
			
			if(input.size() > 3)
			{
				position.first = number / 100 - 1;
				position.second = number % 100 - 1;
			}
			else
			{
				position.first = number / 10 - 1;
				position.second = number % 10 - 1;
			}
			
			break;
		}
		else
			cout << "INVALID ENTRY" << endl;
	}
	
	return position;
}

void HexConsoleUI::drawHexBoard(HexBoard& board)
{
	int rows{ board.getSize() };
	int col, space{0}, slash;

	bool dot, back;
	
	for(int r = 0; r < rows; r++)
	{
		col = 0;
		
		dot = true;
		
		while(col < rows)
		{		
			if(dot)
			{
				switch( board.getCellColor(r, col) )
				{
					case hexColors::BLUE:
						cout << "B"; //cout << "B\u2650";
					break;
					
					case hexColors::RED:
						cout << "R"; //cout << "R\u2648";
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

void HexConsoleUI::updateUI(HexGameEngine* hge)
{
	cout << '\n'; drawHexBoard( hge->getBoard() );
	
	if( hge->getWinner() == &hge->getHuman() )
		cout << "\nHuman Wins, Game Over\n";
	
	if( hge->getWinner() == &hge->getComputer() )
		cout << "\nComputer Wins, Game Over\n";
}

