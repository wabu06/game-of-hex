#include "HexGameEngine.h"


void HexGameEngine::colorCellNeighbor(int Cell)
{
	int row, col;

	vector<int> neighbors = board.getCellNeighbors(Cell, 1, true);
		
	for(auto& N: neighbors)
	{
		if(N >= 0)
		{
			row = N / board.getSize();
			col = N % board.getSize();
				
			if( board.getCellColor(row, col) == hexColors::NONE )
			{
				board.setCellColor( row, col, currentPlayer->getColor() );
				currentPlayer->setPrevCell( row*board.getSize() + col );
				break;
			}
		}
	}
}
	
void HexGameEngine::playComputer()
{
	cout << "\nComputer Takes It's Turn\n";
		
	int pc = currentPlayer->getPrevCell();
		
	bool noColor{true};
		
	int max{0}; int mEnd; // node at end of longest path
	int pSize; // path size
	
	int row, col;
		
		// if computer has a previously colored cell, find longest path from that cell, and color a neighbor at end of longest path
	if(pc >= 0)
	{		
		int bSize = board.getSize()*board.getSize() - 1;
		
		for(int s = 0; s < bSize; s++)
		{
			for(int e = s+1; e <= bSize; e++)
			{
				pSize = currentPlayer->getPath().getPathSize(s, e);
				
				if(pSize > max)
				{
					max = pSize;
					mEnd = e;
				}
			}
		}
		
		if(max == 0) // if there are no connected nodes, connect an uncolored neighbor
		{
			vector<int> pcNeighbors = board.getCellNeighbors(pc, 1, true);

			for(auto& N: pcNeighbors)
			{
				if(N >= 0)
				{
					row = N / board.getSize();
					col = N % board.getSize();
					
					if( board.getCellColor(row, col) == hexColors::NONE )
					{
						board.setCellColor( row, col, currentPlayer->getColor() );
							//currentPlayer->setPrevCell( row*board.getSize() + col );
						break;
					}
				}
			}
		}
		else
		{			// neighbors of node at end of longest path
			vector<int> endNeighbors = board.getCellNeighbors(mEnd, 1, true);
			
			for(auto& N: endNeighbors)
			{
				if(N >= 0)
				{
					row = N / board.getSize();
					col = N % board.getSize();
				
					if( board.getCellColor(row, col) == hexColors::NONE )
					{
						board.setCellColor( row, col, currentPlayer->getColor() );
							//currentPlayer->setPrevCell( row*board.getSize() + col );
							//currentPlayer = &human;
						break;
					}
				}
			}
		}
	}
	else
	{
		row = col = board.getSize() / 2;
			
				// if center cell is not colored, color it, else color a non-colored neighbor, this is the first colored cell
		if( board.getCellColor(row, col) == hexColors::NONE )
		{
			board.setCellColor( row, col, currentPlayer->getColor() );
			currentPlayer->setPrevCell( row*board.getSize() + col );
		}
		else 
		{
			int center = row*board.getSize() + col;
			vector<int> centerNeighbors = board.getCellNeighbors(center, 1, true);
				
			for(auto& N: centerNeighbors)
			{
				if(N >= 0)
				{
					row = N / board.getSize();
					col = N % board.getSize();
					
					if( board.getCellColor(row, col) == hexColors::NONE )
					{
						board.setCellColor( row, col, currentPlayer->getColor() );
						currentPlayer->setPrevCell( row*board.getSize() + col );
						break;
					}
				}
			}
		}
	}
	
		// create edge between cell neighbors that are the same color
	int cell{ row*board.getSize() + col };
		
	vector<int> neighbors = board.getCellNeighbors(cell, 1, true);
		
	for(auto& N: neighbors)
	{
		if(N >= 0)
		{
			if( board.getCellColor(N) == currentPlayer->getColor() )
				currentPlayer->getGraph().addEdge(cell, N, 1);
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
		
	vector<int> neighbors = board.getCellNeighbors(cell, 1, true);
		
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
	
	cout << "win " << human.win();
}

int HexGameEngine::parseInput()
{
	string input; size_t pos{}; int coord{};

	while(true)
	{
		cout << "\nEnter your move, or <q> to quit: "; cin >> input;
		
		if( (input.size() == 1) && (input.front() == 'q') || (input.front() == 'Q') )
		{
			currentPlayer = nullptr;
			run = false;
			throw exception();
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
	{	try { coord = parseInput(); } catch(exception const& exp) { break; }
		
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

void HexGameEngine::generateOutput()
{
	if( (winner == nullptr) && !run )
		return;
	
	int bSize = board.getSize();
	hexColors cc; // board cell color
	
	cout << endl;
	
	for(int r = 0; r < bSize; r++)
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
	}
	
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

