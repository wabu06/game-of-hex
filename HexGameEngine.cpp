#include "HexGameEngine.h"


void HexGameEngine::playHuman(pair<int, int> position)
{
	if(!run) return;
	
	int row{position.first}, col{position.second};
	
	board.setCellColor( row, col, human.getColor() );
		
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

pair<int, int> HexGameEngine::parseInput()
{
	string input; pair<int, int> position;

	while(true)
	{
		cout << "\nEnter selection for your move, or <q> to quit: "; getline(cin, input); //cin >> input;
		
		auto toLowerCase = [](char& c){ c = tolower( c, locale("en_US.UTF8") ); };
	
		for_each(input.begin(), input.end(), toLowerCase);
		
		bool allAlpha = all_of(input.begin(), input.end(), [](char c) { return isalpha( c, locale("en_US.UTF8") ); });
		
		if(allAlpha)
		{
			if( (input == "q") || (input == "quit") || (input == "exit") || (input == "end") )
			{
				currentPlayer = nullptr;
				run = false;
				position.first = position.second = static_cast<unsigned int>('q') * static_cast<unsigned int>('Q');
				break;
			}
		}
		
		bool allDigits = all_of(input.begin(), input.end(), [](char c) { return isdigit( c, locale("en_US.UTF8") ); });
		
		if(allDigits)
		{
			int number = stoi(input, nullptr);
			
			if(input.size() > 3)
			{
				position.first = number / 100;
				position.second = number % 100;
			}
			else
			{
				position.first = number / 10;
				position.second = number % 10;
			}
			
			break;
		}
		else
			cout << "INVALID ENTRY" << endl;
	}
	
	return position;
}

pair<int, int> HexGameEngine::processInput()
{
	hexColors cc; // cell color
	
	bool legal; int size{ board.getSize() - 1 };
	
	int row, col;
	 
	do
	{	pair<int, int> position = parseInput();
	
		if(!run) break;
		
		legal = true;
		
		row = position.first; col = position.second;
		
		if( row < 0 || row > size )
		{
			cout << "ILLEGAL MOVE!\n";
			legal = false;
			continue;
		}
		
		if( col < 0 || col > size )
		{
			cout << "ILLEGAL MOVE!\n";
			legal = false;
			continue;
		}
		
		cc = board.getCellColor(row, col);
		
		if(cc != hexColors::NONE)
		{
			cout << "ILLEGAL MOVE!\n";
			legal = false;
		}
	}
	while(!legal);
	
	return pair<int, int>{row, col};
}

void HexGameEngine::drawHexBoard()
{
	int rows{ board.getSize() }, col{}, space{1};
	
	string dot{"."}, dash{"---"}; string back{"\\"}, forward{"/"}; string curstr;
	
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

		cout << string(space, ' ');
		
		int slash{};

		while(slash < rows)
		{
			cout << curstr;
		
			if(curstr == back)
				{ curstr = forward; slash++; }
			else
				curstr = back;
		
			cout << " "; //cout << string(2, ' ');
		}
	
		cout << "\n"; cout << string(space, ' '); space++;
	}

	cout << endl;
}

void HexGameEngine::generateOutput()
{
	//if( (winner == nullptr) && !run ) // if there's no winner, and run is false it's time quit
		//return;
	
	cout << '\n'; drawHexBoard();
	
	if(winner == &human)
		cout << "\nHuman Wins\n";
	
	if(winner == &computer)
		cout << "\nComputer Wins\n";
}

void HexGameEngine::shutdown()
{
	if(!isInitialized)
		cout << "\nGame Engine Was Not Initialized" << endl;
}

bool HexGameEngine::initialize()
{	
	//cout << "A Game Of Hex\n";
	
	cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n";
	cout << "|A| |G|A|M|E| |O|F| |H|E|X|\n";
	cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n";

	string player;
	
	do
	{	//cout << "\n1) Blue Player\n2) Red Player\n" << string(14, '=') << ">Enter 1 or 2: ";
		cout << "\n1) Blue Player\n2) Red Player\n" << "\u2016\n====>Enter 1 or 2: ";
		getline(cin, player); //cin >> player;
	}
	while( (player.size() > 1) || (player[0] != '1') && (player[0] != '2') );
	
	int size{ board.getSize() };
	
	if (player[0] == '1')
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
	
	return true;
}

