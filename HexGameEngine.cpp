#include "HexGameEngine.h"

		
pair<int, int> HexGameEngine::colorCellNeighbor(int Cell, bool topORright)
{
	int row{-1}, col{-1};

	auto bSize{ board.getSize() };
	
	vector<int> neighbors = board.getCellNeighbors(Cell);
		
	for(auto& N: neighbors)
	{
		row = N / bSize;
		col = N % bSize;
				
		if( board.getCellColor(row, col) == hexColors::NONE )
		{
			if(computer.getColor() == hexColors::BLUE)
			{
				if(topORright)
				{
					if( row < (Cell / bSize) )
					{
						board.setCellColor( row, col, computer.getColor() );
						break;
					}
				}
				else
				{
					if( row > (Cell / bSize) )
					{
						board.setCellColor( row, col, computer.getColor() );
						break;
					}
					
				}
			}
			
			if(computer.getColor() == hexColors::RED)
			{
				if(topORright)
				{
					if( col > (Cell % bSize) )
					{
						board.setCellColor( row, col, computer.getColor() );
						break;
					}
				}
				else
				{
					if( col < (Cell % bSize) )
					{
						board.setCellColor( row, col, computer.getColor() );
						break;
					}
				}
			}
		}
	}

	return pair<int, int>{row, col};
} 
	
void HexGameEngine::playComputer()
{
	cout << "\nComputer Takes It's Turn\n";
	
	static random_device rd{"/dev/urandom"}; 
	static bernoulli_distribution dist{0.5};
	
	static int firstCell{-1};
	
	int row, col;
	
	auto bSize{ board.getSize() };
	
		// find longest path on either side of firstCell
	if(firstCell > 0)
	{
		vector<int> cells = computer.getCurrentCells(firstCell); // account for just one cell colored, and if longest path is at an edge
		
		if(computer.getColor() == hexColors::BLUE)
		{
			bool top = dist(rd); int maxPath{0}; int eNode;
			
			if(top)
			{
				for(auto& c: cells)
				{
					int pSize; int prevMax;
					
					if( (firstCell / bSize) > (c / bSize) ) // comparing rows
					{
						pSize = computer.findPathSize(firstCell, c);
						prevMax = maxPath; maxPath = max(maxPath, pSize);
						
						if(maxPath > prevMax)
							eNode = c;
					}
				}
			}
			else
			{
				for(auto& c: cells)
				{
					int pSize; int prevMax;
					
					if( (firstCell / bSize) < (c / bSize) ) // comparing rows
					{
						pSize = computer.findPathSize(firstCell, c);
						prevMax = maxPath; maxPath = max(maxPath, pSize);
						
						if(maxPath > prevMax)
							eNode = c;
					}
				}
			}
			
			pair<int, int> pos;
			
			if(maxPath == 0)
				pos = colorCellNeighbor(firstCell, top);
			else
				pos = colorCellNeighbor(eNode, top); // all neighbors could be colored
			
			row = pos.first; col = pos.second;
		}
		
		if(computer.getColor() == hexColors::RED)
		{
			bool right = dist(rd); int maxPath{0}; int eNode;
			
			if(right)
			{
				for(auto& c: cells)
				{
					int pSize; int prevMax;
					
					if( (firstCell % bSize) < (c % bSize) ) // comparing columns
					{
						pSize = computer.findPathSize(firstCell, c);
						prevMax = maxPath; maxPath = max(maxPath, pSize);
						
						if(maxPath > prevMax)
							eNode = c;
					}
				}
			}
			else
			{
				for(auto& c: cells)
				{
					int pSize; int prevMax;
					
					if( (firstCell % bSize) > (c % bSize) ) // comparing columns
					{
						pSize = computer.findPathSize(firstCell, c);
						prevMax = maxPath; maxPath = max(maxPath, pSize);
						
						if(maxPath > prevMax)
							eNode = c;
					}
				}
			}
			
			pair<int, int> pos;
			 
			if(maxPath == 0)
				pos = colorCellNeighbor(firstCell, right);
			else
				pos = colorCellNeighbor(eNode, right); // all neighbors could be colored
			
			row = pos.first; col = pos.second;
		}
	}
	else  // if computer has no cells, then check to see if center cell, is colored, and if not color it
	{
		row = col = bSize / 2;
		
				// if center cell is not colored, color it, else color a non-colored neighbor
		if( board.getCellColor(row, col) == hexColors::NONE )
		{
			board.setCellColor( row, col, computer.getColor() );
			firstCell = row*bSize + col;
		}
		else 
		{
			int center = row*bSize + col;
			pair<int, int> pos = colorCellNeighbor( center, dist(rd) ); // all neighbors could be colored
			row = pos.first; col = pos.second;
			
			firstCell = row*bSize + col;
		}
	}
		// create edge between cell neighbors that are the same color
	int cell{ row*board.getSize() + col };

	vector<int> neighbors = board.getCellNeighbors(cell);
		
	for(auto& N: neighbors)
	{
		if(N >= 0)
		{
			if( board.getCellColor(N) == computer.getColor() )
				computer.connectCells(cell, N);
		}
	}
	
	if( computer.win() )
	{
		winner = &computer;
		run = false;
		currentPlayer = nullptr;
	}
	else
		currentPlayer = &human; // computer just played so human plays next
}

void HexGameEngine::playHuman()
{
	//int row, col;
	
	board.setCellColor( hRow, hCol, human.getColor() );
		
			// create edge between cell neighbors that are the same color
	int cell{ hRow*board.getSize() + hCol };
		
	//vector<int> neighbors = board.getCellNeighbors(cell, 1, true);
	vector<int> neighbors = board.getCellNeighbors(cell);
		
	for(auto& N: neighbors)
	{
		if(N >= 0)
		{
			if( board.getCellColor(N) == human.getColor() )
				human.connectCells(cell, N);
		}
	}
	
	if( human.win() )
	{
		winner = &human;
		run = false;
		currentPlayer = nullptr;
	}
	else
		currentPlayer = &computer; // human just played so computer plays next
	
	cout << boolalpha << "win " << human.win();
}

int HexGameEngine::parseInput()
{
	string input; size_t pos{}; int coord{};

	while(true)
	{
		cout << "\nEnter your move, or <q> to quit: "; cin >> input;
		
		//if( (input.size() == 1) && (input.front() == 'q') || (input.front() == 'Q') )
		//{
			//currentPlayer = nullptr;
			//run = false;
			//throw exception();
		//}
		
		if( (input.size() == 1) && ( (input.front() == 'q') || (input.front() == 'Q')) )
		{
			currentPlayer = nullptr;
			run = false;
			coord = static_cast<unsigned int>('q') * static_cast<unsigned int>('Q');
			break;
		}
		
		try
		{
			coord = stoi(input, &pos);
		
			if( (pos == 0) || (pos != input.size()) )
				throw runtime_error("ILLEGAL ENTRY");
			
			break;
		}
		catch(invalid_argument const& exp)
		{
			cout << "ILLEGAL ENTRY" << endl;
		}
		catch(out_of_range const& exp)
		{
			cout << "ILLEGAL ENTRY" << endl;
		}
		catch(runtime_error const& exp)
		{
			cout << "ILLEGAL ENTRY" << endl;
		}
	}
	
	return coord;
}

void HexGameEngine::getHumanInput()
{
	hexColors cc; // cell color
	
	bool legal; int coord, size{ board.getSize() - 1 };
	 
	do
	{	coord = parseInput(); if(!run) break;
		
		legal = true;
		
		hRow = coord / 10; hCol = coord % 10;
		
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
						cout << "b"; //cout << "B\u2650";
					break;
					
					case hexColors::RED:
						cout << "r"; //cout << "R\u2648";
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
	if( (winner == nullptr) && !run )
		return;
	
	//int bSize = board.getSize();
	//hexColors cc; // board cell color
	
	cout << endl; drawHexBoard();
	
	/*for(int r = 0; r < bSize; r++)
	{
		for(int c = 0; c < bSize; c++)
		{
			cc = board.getCellColor(r, c);
			
			switch(cc)
			{
				case hexColors::NONE:
					cout << "[" << r << ", " << c << ", NONE]\t";
				break;
				
				case hexColors::BLUE:
					cout << "[" << r << ", " << c << ", BLUE\u2650]\t";
				break;
				
				case hexColors::RED:
					cout << "[" << r << ", " << c << ", RED\u2648]\t";
				break;
			}
		}
		
		cout << endl;
	}*/
	
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
	cout << "A Game Of Hex\n";

	int player;
	
	do {
		cout << "\n1) Red Player\n2) Blue Player\n\u2193\u2192Enter 1 or 2: ";
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
	
	isInitialized = true;
	
	return true;
}

