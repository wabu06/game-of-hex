#pragma once


#include<iostream>
#include<string>
#include<stdexcept>
#include<utility>
#include<algorithm>
#include<random>
#include<locale>

//#include "HexPlayer.h"
#include "HexBoard.h"
//#include "HexUI.h"


class HexGameEngine
{
	HexPlayer computer, human, *currentPlayer, *winner;
	HexBoard board;
	HexUI* ui;
	
	bool isInitialized;
	bool run;

	bool isMoveLegal();

	void playHuman(pair<int, int> move);
	void playComputer();
	
	void executeGamePlay()
	{
		if(currentPlayer == &human)
		{
			pair<int, int> move;
			bool legal;
			
			do
			{	move = ui->getHumanMove();
			
				if(!run) return; // end game if human choose to quit instead of entering a move
			
				legal = isMoveLegal(move);
			}
			while(!legal);
			
			playHuman(move);
			return;
		}
		
		if(currentPlayer == &computer)
			playComputer();
	}
	
	pair<int, int> colorCellNeighbor(int cell);
	
	pair<int, int> findLongestPath(int cell);
	
	pair<int, int> extendLongestPath();
	
	pair<int, int> makeWinMove(HexPlayer player);
	
	public:
		HexGameEngine(int size = 7): winner(nullptr), board( HexBoard(size) ), ui(nullptr), isInitialized(false), run(true) {}

		bool initialize();
		
		void runLoop()
		{
			if(!isInitialized) // insures initialize method is called first
				return;
	
			if(currentPlayer == &human)
				ui->generateOutput();

			while(run)
			{
				executeGamePlay(); // update player graphs and gameBoard
				
				if( (winner == nullptr) && !run ) continue; // if there's no winner, and run is false it's time quit
				
				ui->generateOutput();
			}
		}
		
		void shutdown()
		{
			if(!isInitialized)
				cout << "\nGame Engine Was Not Initialized" << endl;
	
			if(ui != nullptr)
				delete ui;
		}
};

