/*
*
* A Game Of Hex
*
* By: Warren Burke
*
*/


#include "HexGameEngine.h"


pair<bool, pair<int, int>> HexGameEngine::colorCellNeighbor(int cell)
{
	int row{-1}, col{-1};
	
	bool colored{false};

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
			board.setCellColor(row, col, computer.getColor(), computer);
			colored = true;
			break;
		}
		
		row = col = -1;
	}

	return { colored, pair<int, int>{row, col} };
} 

multimap<int, int, greater<int>> HexGameEngine::findPathSizes(int cell)
{
	vector<int> cells = computer.getCurrentCells(cell);
	
	if( cells.size() == 2 )
	{
		int pSize = computer.findPathSize(cells[0], cells[1]);
		
		if(pSize != 0)
		{
			return multimap<int, int, greater<int>> {
					{pSize, cells[0]}, {pSize, cells[1]} 
			};
		}
		else
			return multimap<int, int, greater<int>>{};
	}

	int pSize; // path size

	multimap<int, int, greater<int>> pathMap{};

	auto itr = cells.begin(); itr++;

	for(auto& B: cells)
	{ 
		for(auto E = itr; E < cells.end(); E++)
		{
			pSize = computer.findPathSize(B, *E);
			pathMap.insert( {{pSize, B}, {pSize, *E}} );
		}
		itr++;
	}

	return pathMap;
}

pair<int, int> HexGameEngine::extendLongestPath()
{
	static int prevCell{-1};
	
	int row, col;
	
	//if(prevCell > 0)
	if(computer.getCellCount() > 1)
	{
		auto pSizes{ findPathSizes(prevCell) };
		
		auto bSize{ board.getSize() };
		
		pair<int, int> position;
		
		bool colored;
		
		for(const auto& [size, cell]: pSizes)
		{
			if(computer.getColor() == hexColors::BLUE)
			{
				auto r = cell / bSize;
				
				if(r == 0 || r == (bSize - 1))
					continue;
			}
			
			if(computer.getColor() == hexColors::RED)
			{
				auto c = cell % bSize;
				
				if(c == 0 || c == (bSize - 1))
					continue;
			}
			
			
			tie(colored, position) = colorCellNeighbor(cell);
			
			if(colored) {
				prevCell = cell;
				break;
			}
		}

		row = position.first; col = position.second;
		
		return {row, col};
	}
	else  
	{
		if(computer.getCellCount() == 1) {
			auto [colored, position] = colorCellNeighbor(prevCell);
			row = position.first; col = position.second;
		}
		else // if computer has no cells, pick a random cell
		{
			do {
				prevCell = board.getRandCell();
			}
			while(board.getCellColor(prevCell) != hexColors::NONE);
			
			auto bSize{ board.getSize() };
			
			row = prevCell / bSize;
			col = prevCell % bSize;
			
			board.setCellColor(row, col, computer.getColor(), computer);
		}
	}
	
	return pair<int, int>{row,col};
}

void HexGameEngine::playComputer()
{
	ui->displayMsg("\nComputer Takes It's Turn\n");
	
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
		done = true;
		currentPlayer = nullptr;
	}
	else
		currentPlayer = &human; // computer just played so human plays next
}

