/*
*
* A Game Of Hex
*
* By: Warren Burke
*
*/


#include "HexGameEngine.h"


using namespace std::chrono;


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
		
		for(int reps = 0; reps <= 10000; reps++)
		{
			simBoard.setCellColor(cell, simColor); // cell currently under consideration
		
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
	
	auto lessThan = [](const pair<int, int> &e1, const pair<int, int> &e2)->bool { return e1.second < e2.second; };
	
	auto mapMax = max_element(winMap.begin(), winMap.end(), lessThan); // get move with the most wins
	
	return mapMax->first;
}

void HexGameEngine::playComputer()
{
	ui->displayMsg("\nComputer Takes It's Turn\n");

	int cell { genMonteMove() };
	
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

