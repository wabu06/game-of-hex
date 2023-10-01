/*
*
* A Game Of Hex
*
* By: Warren Burke
*
*/


#include "HexGameEngine.h"


using namespace std::chrono;

//#if MONTE

			// generates moves via monte carlo simulation
int HexGameEngine::genMonteMove()
{
	//shuffleMax = level * shuffleMax / 3;
	
	int shuffleMax{2421};
	
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
	
	int nones = board.getNoneCount();
	
	if(nones < 10)
		generateMove = &HexGameEngine::genMiniMaxMove;
	
	algo = "monte";
	
	return cell; //return mapMax->first;
}

//#else

GameState HexGameEngine::getMinMax(GameState hgs, int depth, bool max, int alpha)
{
	//fout << depth << '\n';
	
	auto size { hgs.board.getSize() };
	size *= size;
	
	vector<GameState> hgsV;
	
	int alphaMax, betaMin;
	alphaMax = betaMin = alpha;

		// get all possible states relative to current state
	for(int c = 0; c < size; c++)
	{
		if(hgs.board.getCellColor(c) == hexColors::NONE)
		{
			GameState mmhgs = hgs;
			
			mmhgs.cell = c;
			
			//fout << "c- " << c << '\n' << "mmhgs - " << mmhgs.cell << '\n';
			
			if(max)
			{
				mmhgs.board.setCellColor(c, hgs.computer.getColor());
				
				auto neighbors = mmhgs.board.getCellNeighbors(c);
				
				for(auto& n: neighbors)
				{
					if(mmhgs.board.getCellColor(n) == mmhgs.computer.getColor())
						mmhgs.computer.connectCells(c, n);
				}
				
				if( mmhgs.computer.win() ) {
					vector<int> wp = mmhgs.computer.winPath();

					int wplen = wp.size();
					int avg = accumulate(wp.begin(), wp.end(), 0) / wplen;
					
					mmhgs.value = size - avg;

					//mmhgs.value = 2;
					//return mmhgs;
				}
				else
				{
					if(mmhgs.board.gotDraw()) // draw
						mmhgs.value = 0;
					else
					{
						if(depth == 0)
							//mmhgs.value = size * size;
							mmhgs.value = 1;
						else
							mmhgs = getMinMax(mmhgs, depth - 1, !max, alphaMax); // * -1);
					}
				}
				
				alphaMax = mmhgs.value > alphaMax ? mmhgs.value: alphaMax;
			}
			else
			{
				mmhgs.board.setCellColor(c, hgs.human.getColor());
				
				auto neighbors = mmhgs.board.getCellNeighbors(c);
				
				for(auto& n: neighbors)
				{
					if(mmhgs.board.getCellColor(n) == mmhgs.human.getColor())
						mmhgs.human.connectCells(c, n);
				}
				
				if( mmhgs.human.win() ) {
					vector<int> wp = mmhgs.human.winPath();

					int wplen = wp.size();
					int avg = accumulate(wp.begin(), wp.end(), 0) / wplen;

					mmhgs.value = (size - avg); // * -1;

					//mmhgs.value = accumulate(p.begin(), p.end(), 0);// * -1;
					//mmhgs.value = -2;
					//return mmhgs;
				}
				else
				{
					if(mmhgs.board.gotDraw()) // draw
						mmhgs.value = 0;
					else
					{
						if(depth == 0)
							//mmhgs.value = -1 * size * size;
							mmhgs.value = 1;
						else
							mmhgs = getMinMax(mmhgs, depth - 1, !max, 0);
					}
				}
				
				if(mmhgs.value <= betaMin) {
					hgsV.push_back(mmhgs);
					break;
				}
			}
			
			hgsV.push_back(mmhgs);
			
			//fout << "cmpHGS - " << cmpHGS.cell << '\n';
		}
	}

	if(max)
		return *max_element(hgsV.begin(), hgsV.end(), [](GameState lgs1, GameState lgs2)->bool { return lgs1.value < lgs2.value; });
	else
		return *min_element(hgsV.begin(), hgsV.end(), [](GameState lgs1, GameState lgs2)->bool { return lgs1.value > lgs2.value; });
}

// Alpha Beta:
//	-While iterating at a max level, if recursed into a min pass the current max(alpha) to min level
//	-At min level while iterating compare current computed value to current max passed in from max level
//	-If current computed value at min level is less or equal to the max level value,
//		return current computed min value back to max level, otherwise continue at min level
//	-When recursing into max level from min level reset alpha to 0.

	// generates moves via minimax
int HexGameEngine::genMiniMaxMove()
{
	GameState hgs = {computer, human, board, -1, -1};
	
	//auto size = board.getSize(); size *= size;
	auto none = board.getNoneCount();
	
	//fout.open("cells.txt");
	
	double depth = floor( log10(388000000) / log10(none) );
	//double depth = floor( log10(388000) / log10(none) );
	
	//static double depth{3.28};
	
	ui->displayMsg("depth is: " + to_string(depth) );
	
	auto start = high_resolution_clock::now();
	
	//auto state = getMinMax(hgs, (int) floor(depth), true);
	auto state = getMinMax(hgs, (int) depth, true, 0);
	//auto state = getMinMax(hgs, -1, true);
	
	auto stop = high_resolution_clock::now();
	
	//duration<double, milli> elapse = stop - start;
	duration<double> elapse = stop - start;

	ui->displayMsg("Computer's Elapsed Time: " + to_string( elapse.count() ) + " seconds");
	algo = "minmax";
	
	//depth += 1.0 / 3.0;
	
	//ui->displayMsg("\ncomputer's elapsed time: " + to_string(elapse.count()/1000.0) + " seconds\n");
	
	//fout.close();
	
	return state.cell;

	//random_device rd{"/dev/urandom"};
	
	//ofstream fout("depth.txt"); //fout << cells << '\t';
}

//#endif

void HexGameEngine::playComputer()
{
	ui->displayMsg("Computer Takes It's Turn");
	
	int cell = (this->*generateMove)();

/*#if MONTE
	int cell { genMonteMove() };
#else
	int cell { genMiniMaxMove() };
#endif*/
	 
	auto size{ board.getSize() };
	
	ui->displayMsg("Computer selects cell (" + to_string(cell / size + 1) + ", " + to_string(cell % size + 1) + "), via - " + algo);
	
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
	else {
		currentPlayer = &human; // computer just played so human plays next
		playCurrentPlayer = &HexGameEngine::playHuman;
	}
}

