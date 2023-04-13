//#include "HexConsoleUI.h"

#include "HexGameEngine.h"

int HexConsoleUI::getHumanPlayer()
{
	int player;

	do
	{	cout << "\n1) Blue Player\n2) Red Player\n" << "\u2016\nV==>Enter 1 or 2: ";
		cin >> player;

		string badstr;
		
		if(cin.fail())
		{
			cin.clear();
			getline(cin, badstr);
			player = -1;
			continue;
		}
		
		getline(cin, badstr);
		
		if(badstr.size() > 0)
			player = -1;
	}
	while( (player != 1) && (player != 2) );
	
	return player;
}

pair<int, int> HexConsoleUI::getHumanMove(HexGameEngine* hge)
{
	string input;
	
	int move, row, col;

	auto toLowerCase = [](char& c){ c = tolower( c, locale("en_US.UTF8") ); };

	while(true)
	{
		cout << "\nEnter your move, or <h> for help, or <q> to quit: ";
		cin >> move;
		
		if(cin.fail())
		{
			cin.clear();
			getline(cin, input);
			
			for_each(input.begin(), input.end(), toLowerCase);
			
			if( (input == "q") || (input == "quit") || (input == "exit") || (input == "end") )
			{
				hge->setCurrentPlayer(nullptr);
				hge->endGame();
				row = col = static_cast<unsigned int>('q') * static_cast<unsigned int>('Q');
				break;
			}
			
			if( (input == "h") || (input == "help") )
			{
				cout << "\nIf for example you want to select the cell at row 5, & column 2, simply enter 52.\n";
				cout << "Or if you wanted to select the cell at row 7, & column 11, enter 0711.\n";
			}
			continue;
		}
		
		getline(cin, input);
		
		if(input.size() > 0)
			continue;
			
		input = to_string(move);

		if(input.size() > 3)
		{
			row = move / 100 - 1;
			col = move % 100 - 1;
			break;
		}
		else
		{
			row = move / 10 - 1;
			col = move % 10 - 1;
			break;
		}
	}
	
	return {row, col};
}

void HexConsoleUI::drawHexBoard(HexBoard& board)
{
	int rows{ board.getSize() }, col{}, space{0};
	
	string dot{"."}, dash{"---"}; //dash{"---"}
	string back{"\\"}, forward{"/"}; string curstr;
	
	for(int r = 0; r < rows; r++)
	{
		curstr = dot; col = 0; // dot column, matches dot with board column
		
		while(col < rows)
		{		
			if(curstr == dot)
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
						cout << curstr;
				}
			
				curstr = dash; col++;
			}
			else
				{ cout << curstr; curstr = dot;}
		}
		
		if( r == (rows-1) ) continue;
	
		cout << "\n"; curstr = back;

		space++; cout << string(space, ' ');
		
		int slash{};

		while(slash < rows)
		{
			cout << curstr;
		
			if(curstr == back)
				{ curstr = forward; slash++; }
			else
				curstr = back;
		
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
		cout << "\nHuman Wins\n";
	
	if( hge->getWinner() == &hge->getComputer() )
		cout << "\nComputer Wins\n";
}

