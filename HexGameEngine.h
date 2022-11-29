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
	//HexUI* ui;
	
	bool isInitialized;
	bool run;
	
	pair<int, int> parseInput();
	
	pair<int, int> processInput();

	void playHuman(pair<int, int> position);
	void playComputer();
	
	void executeGamePlay()
	{
		if(currentPlayer == &human)
		{
			playHuman( processInput() );
			return;
		}
		
		if(currentPlayer == &computer)
			playComputer();
	}
	
	void drawHexBoard();
	
	void generateOutput();

	//pair<int, int> colorCellNeighbor(int Cell, bool topORright);
	pair<int, int> colorCellNeighbor(int cell);
	
	pair<int, int> findLongestPath(int cell);
	
	pair<int, int> extendLongestPath();
	
	public:
		HexGameEngine(int size = 7): winner(nullptr), board( HexBoard(size) ), isInitialized(false), run(true) {}

		bool initialize();
		
		void runLoop()
		{
			if(!isInitialized) // insures initialize method is called first
				return;
	
			if(currentPlayer == &human)
				generateOutput();

			while(run)
			{
				executeGamePlay(); // update player graphs and gameBoard
				
				if( (winner == nullptr) && !run ) continue; // if there's no winner, and run is false it's time quit
				
				generateOutput();
			}
		}
		
		void shutdown();
};

