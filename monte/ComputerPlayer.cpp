/*
*
* A Game Of Hex
*
* By: Warren Burke
*
*/


#include "HexGameEngine.h"

#include<fstream>


using namespace std::chrono;


int HexGameEngine::genMonteMove(int shuffleMax)
{
	int size{ board.getSize() }, cells{size*size};
	
	vector<int> vacancies;
	
	for(int c = 0; c < cells; c++)
	{
		if( board.getCellColor(c) == hexColors::NONE )
			vacancies.push_back(c);
	}
	
	random_device rd{"hw"}; mt19937 eng( rd() );
	
	hexColors simColor = computer.getColor();
	
	HexPlayer simPlayer(computer);
	HexBoard simBoard(board);
	
	hexColors current{ human.getColor() };

	vector< vector<int> > winPaths; // possible winning path for computer player
	
	vector<int> path;
	
	ofstream fout("paths.txt");
	
	auto start = high_resolution_clock::now();
	
	for(int reps = 0; reps <= shuffleMax; reps++)
	{
		shuffle(vacancies.begin(), vacancies.end(), eng);
		
		for(auto& c: vacancies)
		{
			simBoard.setCellColor(c, current);
			
			if( current == human.getColor() )
				current = simColor;
			else
			{
				vector<int> neighbors = simBoard.getCellNeighbors(c);
							
				for(auto& N: neighbors) // update computer sim player graph
				{
					if( simBoard.getCellColor(N) == simPlayer.getColor() )
						simPlayer.connectCells(c, N);
				}
				current = human.getColor();
			}
		}
		
		path = simPlayer.winPath();
		
		for(auto& n: path)
			fout << n << '\t';
		
		fout << '\n';

		if(path.size() > 0)
			winPaths.push_back(path);
		
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
	
	//ui->displayMsg("\npaths size: " + to_string(winPaths.size()) + '\n');
	
	ui->displayMsg("\nComputer's Elapsed Time: " + to_string( elapse.count() ) + " seconds\n");
	
	auto lessThan = [](const pair<int, int> &e1, const pair<int, int> &e2)->bool { return e1.second < e2.second; };
	
	auto mapMax = max_element(cellCountMap.begin(), cellCountMap.end(), lessThan); // get move with the most wins
	
	fout << mapMax->first << '\n'; fout.close();
	
	return mapMax->first;
}

	// generates moves via monte carlo simulation
int HexGameEngine::genMonteMove()
{
	int size{ board.getSize() }, cells{size*size};
	//int row{-5}, col{-5};
	
	vector<int> vacancies;
	
	for(int c = 0; c < cells; c++)
	{
		if( board.getCellColor(c) == hexColors::NONE )
			vacancies.push_back(c);
	}
	
	hexColors simColor = computer.getColor();
	
	HexPlayer simPlayer(computer);
	HexBoard simBoard(board);
	
	vector<int> simVacancies = vacancies; //vector<int>();
	
	random_device rd{"hw"}; mt19937 eng( rd() );
	
	hexColors current{ human.getColor() };
	
	unordered_map<int,int> winMap; // frequency map of winnning moves
	
	auto start = high_resolution_clock::now();
	
	//cout << "vacancies: " << vacancies.size() << '\n';
	
	for(auto& cell: vacancies)
	{
		//auto cell = vacancies.back(); vacancies.pop_back();
		
		remove(simVacancies.begin(), simVacancies.end(), cell);
		
		for(int reps = 0; reps <= 5000; reps++)
		{
			simBoard.setCellColor(cell, simColor); // cell currently under consideration
			
			vector<int> neighbors = simBoard.getCellNeighbors(cell);
							
			for(auto& N: neighbors) // update computer sim player graph
			{
				if( simBoard.getCellColor(N) == simPlayer.getColor() )
					simPlayer.connectCells(cell, N);
			}
		
			//simVacancies = vacancies;
			//remove(simVacancies.begin(), simVacancies.end(), cell); // remove cell currently under consideration
		
			shuffle(simVacancies.begin(), simVacancies.end(), eng);

			for(auto& c: simVacancies)
			{
				simBoard.setCellColor(c, current);
			
				if( current == human.getColor() )
					current = simColor;
				else
				{
					vector<int> neighbors = simBoard.getCellNeighbors(c);
							
					for(auto& N: neighbors) // update computer sim player graph
					{
						if( simBoard.getCellColor(N) == simPlayer.getColor() )
							simPlayer.connectCells(c, N);
					}
					current = human.getColor();
				}
			}

			if( simPlayer.win() )
				++winMap[cell];

				// reset board & player for next round of simulation
			simPlayer = computer;
			simBoard = board;
		}
		
		simVacancies.push_back(cell);
	}
	
	auto stop = high_resolution_clock::now();
	
	//duration<double, milli> elapse = stop - start;
	duration<double> elapse = stop - start;
	
	//ui->displayMsg("\ncomputer's elapsed time: " + to_string(elapse.count()/1000.0) + " seconds\n");
	ui->displayMsg("\nComputer's Elapsed Time: " + to_string( elapse.count() ) + " seconds\n");

	if(winMap.size() < 1)
		return vacancies.back();
	
	auto lessThan = [](const pair<int, int> &e1, const pair<int, int> &e2)->bool { return e1.second < e2.second; };
	
	auto mapMax = max_element(winMap.begin(), winMap.end(), lessThan); // get move with the most wins
	
	return mapMax->first;
}

void HexGameEngine::playComputer()
{
	ui->displayMsg("\nComputer Takes It's Turn\n");

	int cell { genMonteMove(5000) };
	
	board.setCellColor(cell, computer.getColor(), computer);

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

