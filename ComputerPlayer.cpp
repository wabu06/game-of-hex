/*
*
* A Game Of Hex
*
* By: Warren Burke
*
*/


#include "HexGameEngine.h"


pair<int, int> HexGameEngine::colorCellNeighbor(int cell)
{
	int row{-1}, col{-1};

	auto bSize{ board.getSize() };
	
	vector<int> neighbors;
	
	if(computer.getColor() == hexColors::BLUE)
		neighbors = board.getBlueNeighbors(cell);
	
	if(computer.getColor() == hexColors::RED)
		neighbors = board.getRedNeighbors(cell);
	
	for(auto& N: neighbors)
	{
		row = N / bSize;
		col = N % bSize;
		
		if( board.getCellColor(row, col) == hexColors::NONE )
		{
			board.setCellColor( row, col, computer.getColor() );
			break;
		}
		
		row = col = -1;
	}

	return pair<int, int>{row, col};
} 

pair<int, int> HexGameEngine::findLongestPath(int cell)
{
	pair<int, int> endpoints{-1, -1};
	
	vector<int> cells = computer.getCurrentCells(cell);
	
	if( cells.size() < 2 )
		return endpoints;
		
	int prevMax, maxPath{0}, bNode, eNode;

	int pSize; // path size

	auto itr = cells.begin(); itr++;

	for(auto& B: cells)
	{ 
		for(auto E = itr; E < cells.end(); E++)
		{
			if( B != *E)
			{ 
				pSize = computer.findPathSize(B, *E);
				prevMax = maxPath; maxPath = max(maxPath, pSize);

				if(maxPath > prevMax)
				{
						endpoints.first = B;
						endpoints.second = *E;
				}
			}
		}
		itr++;
	}

	return endpoints;
}

pair<int, int> HexGameEngine::extendLongestPath()
{
	static int prevCell{-1};
	
	auto bSize{ board.getSize() };
	
	int row, col;
	
	if(prevCell > 0)
	{
		pair<int, int> endpoints{ findLongestPath(prevCell) };
		
		pair<int, int> position;
		
		if(endpoints.first == -1 && endpoints.second == -1)
		{
			position = colorCellNeighbor(prevCell);
			row = position.first; col = position.second;
		}
		else
		{
			position = colorCellNeighbor(endpoints.second);
		
			prevCell = endpoints.second;
		
			row = position.first; col = position.second;
		
			if(row == -1 && col == -1)
			{
				position = colorCellNeighbor(endpoints.first);

				prevCell = endpoints.first;
		
				row = position.first; col = position.second;
			}
		}
	}
	else  // if computer has no cells, then check to see if center cell, is colored, and if not color it
	{
		row = col = bSize / 2;
		
				// if center cell is not colored, color it, else color a non-colored neighbor
		if( board.getCellColor(row, col) == hexColors::NONE )
		{
			board.setCellColor( row, col, computer.getColor() );
			prevCell = row*bSize + col;
		}
		else 
		{
			int center = row*bSize + col;
			pair<int, int> position = colorCellNeighbor(center); // all neighbors could be colored
			row = position.first; col = position.second;
			
			prevCell = row*bSize + col;
		}
	}
	
	return pair<int, int>{row,col};
}

void HexGameEngine::playComputer()
{
	cout << "\nComputer Takes It's Turn\n";
	
	//static int prevCell{-1};
	
	pair<int, int> position { extendLongestPath() };
	
	auto row{ position.first }, col{ position.second };
	
	auto bSize{ board.getSize() };

		// create edge between cell neighbors that are the same color
	int cell{ row*bSize + col };

	vector<int> neighbors = board.getCellNeighbors(cell);
		
	for(auto& N: neighbors)
	{
		if( board.getCellColor(N) == computer.getColor() )
			computer.connectCells(cell, N);
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

