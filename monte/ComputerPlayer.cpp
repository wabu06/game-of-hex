/*
*
* A Game Of Hex
*
* By: Warren Burke
*
*/


#include "HexGameEngine.h"


using namespace std::chrono;

#if MONTE

			// generates moves via monte carlo simulation
int HexGameEngine::genMonteMove(int shuffleMax)
{
	shuffleMax = level * shuffleMax / 3;
	
	int size{ board.getSize() }, cells{size*size};
	
	vector<int> vacancies;
	
	for(int c = 0; c < cells; c++)
	{
		if( board.getCellColor(c) == hexColors::NONE )
			vacancies.push_back(c);
	}
	
	//random_device rd{"/dev/urandom"}; mt19937 eng( rd() );

	hexColors manColor{ human.getColor() }, cmpColor{ computer.getColor() }, current{ cmpColor };
	
	HexPlayer simPlayer(computer);
	HexBoard simBoard(board);

	vector< vector<int> > winPaths; // possible winning paths for computer player
	
	vector<int> path;
	
	ofstream fout("paths.txt");
	
	auto start = high_resolution_clock::now();
	
	for(int reps = 0; reps <= shuffleMax; reps++)
	{
		shuffle(vacancies.begin(), vacancies.end(), rd);
		
		for(auto& c: vacancies)
		{
			simBoard.setCellColor(c, current);
			
			if(current == cmpColor)
			{
				vector<int> neighbors = simBoard.getCellNeighbors(c);
							
				for(auto& N: neighbors) // update computer sim player graph
				{
					if( simBoard.getCellColor(N) == simPlayer.getColor() )
						simPlayer.connectCells(c, N);
				}
			}
			
			current = current == manColor ? cmpColor: manColor;
		}
		
		path = simPlayer.winPath();

		if(path.size() > 0)
		{
			winPaths.push_back(path);

			for(auto& n: path)
				fout << n << '\t';
			fout << '\n';
		}
		
			// reset board & player for next round of simulation
		simPlayer = computer;
		simBoard = board;
	}
	
	unordered_set<int> vacant(vacancies.begin(), vacancies.end());
	
	unordered_map<int,int> cellCountMap;
	
	for(auto& P: winPaths)
	{
		for(auto& c: P)
		{
			if( vacant.find(c) != vacant.end() )
				++cellCountMap[c];
		}
	}

	auto stop = high_resolution_clock::now();
	
	duration<double> elapse = stop - start;
	
	ui->displayMsg("Computer's Elapsed Time: " + to_string( elapse.count() ) + " seconds");
	
	auto lessThan = [](const pair<int, int> &e1, const pair<int, int> &e2)->bool { return e1.second < e2.second; };
	
	//auto mapMax = max_element(cellCountMap.begin(), cellCountMap.end(), lessThan); // get move with the most wins
	
		// returns a pointer to a pair, so must dereference 1st
		// find most frequently recurring cell among winning paths
	auto [cell, count] = *max_element(cellCountMap.begin(), cellCountMap.end(), lessThan); 
	
	//fout << mapMax->first << '\n'; fout.close();
	
	fout << "cell: " << cell << '\t' << "count: " << count << '\n'; fout.close();
	
	return cell; //return mapMax->first;
}

#else

maxTuple HexGameEngine::getMax(HexPlayer& maxPlayer, HexPlayer& minPlayer, HexBoard& maxBoard, vector<int> unColored, int move,
								unordered_map<int, hexColors> colored, ofstream& fout, int depth, bool max)
{
	fout << depth << '\n';
	
	if(unColored.size() == 0)
		return {0, move, unColored, colored};
	
	for(auto& [cell, color]: colored)
	{
		maxBoard.setCellColor(cell, color);
		
		vector<int> neighbors = maxBoard.getCellNeighbors(cell);
		
		if(maxPlayer.getColor() == color)
		{
			for(auto& N: neighbors)
			{
				if( maxBoard.getCellColor(N) == maxPlayer.getColor() )
					maxPlayer.connectCells(cell, N);
			}
		}
		
		if(minPlayer.getColor() == color)
		{
			for(auto& N: neighbors)
			{
				if( maxBoard.getCellColor(N) == minPlayer.getColor() )
					minPlayer.connectCells(cell, N);
			}
		}	
	}
	
	if(max)
	{
		maxBoard.setCellColor(move, maxPlayer.getColor());
		
		vector<int> neighbors = maxBoard.getCellNeighbors(move);
		
		for(auto& N: neighbors)
		{
			if( maxBoard.getCellColor(N) == maxPlayer.getColor() )
				maxPlayer.connectCells(move, N);
		}
		
		colored[move] = maxPlayer.getColor();
	}
	else
	{
		maxBoard.setCellColor(move, minPlayer.getColor());
		
		vector<int> neighbors = maxBoard.getCellNeighbors(move);
		
		for(auto& N: neighbors)
		{
			if( maxBoard.getCellColor(N) == minPlayer.getColor() )
				minPlayer.connectCells(move, N);
		}
		
		colored[move] = minPlayer.getColor();
	}

	if(maxPlayer.win() && max)
	{
		//vector<int> path = maxPlayer.winPath();
		
		//auto pSum = accumulate(path.begin(), path.end(), (rd() % (board.getSize() + 1))); //path.size());
		
		//auto bSize = board.getSize();
		
		//return {bSize * bSize - path.size(), move, unColored, colored};
		return {1, move, unColored, colored};
	}
		//return {rd() % (board.getSize() + 1), move, unColored, colored};
	/*{
		vector<int> path = maxPlayer.winPath();
		
		auto bSize = board.getSize();
		
		if(maxPlayer.getColor() == hexColors::BLUE)
		{
			auto crange = (path[path.size() - 1] % bSize) - (path[0] % bSize);
			
			crange = crange < 0 ? -1 * crange : crange;
			
			return {bSize - crange + 1, move, unColored, colored};
		}
		else
		{
			auto rrange = (path[path.size() - 1] / bSize) - (path[0] / bSize);
			
			rrange = rrange < 0 ? -1 * rrange : rrange;
			
			return {bSize - rrange + 1, move, unColored, colored};
		}
	}*/
	
	if(minPlayer.win() && !max)
	{
		//vector<int> path = minPlayer.winPath();
		
		//auto pSum = accumulate(path.begin(), path.end(), (rd() % (board.getSize() + 1))); //path.size());

		//auto bSize = board.getSize();
		
		//return {-1 * (bSize * bSize - path.size()), move, unColored, colored};
		return {-1, move, unColored, colored};
	}
		//return {-1 * (rd() % (board.getSize() + 1)), move, unColored, colored};
	/*{
		vector<int> path = minPlayer.winPath();
		
		auto bSize = board.getSize();
		
		if(minPlayer.getColor() == hexColors::BLUE)
		{
			auto crange = (path[path.size() - 1] % bSize) - (path[0] % bSize);
			
			crange = crange < 0 ? -1 * crange : crange;
			
			return {-1 * (bSize - crange + 1), move, unColored, colored};
		}
		else
		{
			auto rrange = (path[path.size() - 1] / bSize) - (path[0] / bSize);
			
			rrange = rrange < 0 ? -1 * rrange : rrange;
			
			return {-1 * (bSize - rrange + 1), move, unColored, colored};
		}
	}*/

	maxBoard = board; // reset maxBoard
	maxPlayer = computer;
	minPlayer = human;
	
	vector<maxTuple> states; // game state in a tree node
	
	for(auto& cell: unColored)
	{
		vector<int> tmpColored = unColored;
		
		remove(tmpColored.begin(), tmpColored.end(), cell);
		
		auto state = getMax(maxPlayer, minPlayer, maxBoard, tmpColored, cell, colored, fout, depth + 1, !max);
		states.push_back(state);
	}

	auto lessThan = [](const maxTuple t1, const maxTuple t2)->bool {
							return get<0>(t1) < get<0>(t2);
						};
	
	auto greaterThan = [](const maxTuple t1, const maxTuple t2)->bool {
							return get<0>(t1) > get<0>(t2);
						};
	
	if(max) {
		auto [val, maxMove, maxUnColored, maxColored] = *max_element(states.begin(), states.end(), lessThan);
		return {val, move, unColored, colored};
	}
	else {
		auto [val, minMove, minUnColored, minColored] = *min_element(states.begin(), states.end(), greaterThan);
		return {val, move, unColored, colored};
	}
}

	// generates moves via minimax
int HexGameEngine::genMiniMaxMove()
{
	int size{ board.getSize() }, cells{size*size};
	
	vector<int> vacants;
	
	for(int c = 0; c < cells; c++)
	{
		if( board.getCellColor(c) == hexColors::NONE )
			vacants.push_back(c);
	}

	HexPlayer maxPlayer(computer), minPlayer(human);
	HexBoard maxBoard(board);

	vector<maxTuple> states; // game state in a tree node
	
	random_device rd{"/dev/urandom"};
	
	ofstream fout("depth.txt"); //fout << cells << '\t';
	
	auto start = high_resolution_clock::now();
	
	for(auto& cell: vacants)
	{
		vector<int> tmpVacants = vacants;
		
		remove(tmpVacants.begin(), tmpVacants.end(), cell);
		
		auto state = getMax(maxPlayer, minPlayer, maxBoard, tmpVacants, cell, unordered_map<int, hexColors>{}, fout, 0, true);
		states.push_back(state);
	}

	auto lessThan = [](const maxTuple t1, const maxTuple t2)->bool {
							return get<0>(t1) < get<0>(t2);
						};
	
	auto [val, move, unColored, colored] = *max_element(states.begin(), states.end(), lessThan);
	
	auto stop = high_resolution_clock::now();
	
	//duration<double, milli> elapse = stop - start;
	duration<double> elapse = stop - start;
	
	fout.close();

	ui->displayMsg("Computer's Elapsed Time: " + to_string( elapse.count() ) + " seconds");
	
	//ui->displayMsg("\ncomputer's elapsed time: " + to_string(elapse.count()/1000.0) + " seconds\n");
	
	return move;
}

#endif

void HexGameEngine::playComputer()
{
	ui->displayMsg("Computer Takes It's Turn");

#if MONTE
	int cell { genMonteMove() };
#else
	int cell { genMiniMaxMove() };
#endif
	 
	auto size{ board.getSize() };
	
	ui->displayMsg("Computer selects cell (" + to_string(cell / size + 1) + ", " + to_string(cell % size + 1) + ")");
	
	board.setCellColor( cell, computer.getColor() );

	vector<int> neighbors = board.getCellNeighbors(cell);
		
		// update computer player graph
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

