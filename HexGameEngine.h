#pragma once


#include<iostream>
#include<string>
#include<stdexcept>

//#include "graph.h"
#include "hex.h"
//#include "bfs.h"
//#include "dfs.h"
#include "HexPlayer.h"
#include "HexBoard.h"
//#include "HexUI.h"


class HexGameEngine
{
	HexPlayer computer, human, *currentPlayer, *winner;
	HexBoard board;
	//HexUI* ui;
	
	bool isInitialized;
	bool run; //stop
	
	int hRow{}, hCol{}; // row & column selection of human player
	
	int parseInput();
	void getHumanInput();
	
	void processInput()
	{
		if(currentPlayer == &human)
			getHumanInput();
	}

	void playHuman();
	void playComputer();
	
	void executeGamePlay()
	{
		if(currentPlayer == &human)
		{
			playHuman();
			//currentPlayer = &computer;
			return;
		}
		
		if(currentPlayer == &computer)
		{
			playComputer();
			//currentPlayer = &human;
		}
	}
	
	void generateOutput();

	void colorCellNeighbor(int Cell);
	
	public:
		HexGameEngine(int size = 7): isInitialized(false), run(true), winner(nullptr), board( HexBoard(size) ) {}

		bool initialize();
		
		void runLoop() // or run()
		{
			if(!isInitialized)
				return;

			generateOutput();

			while(run)
			{
				processInput();
				executeGamePlay(); // update player graphs and gameBoard
				generateOutput();
			}
		}
		
		void shutdown();
};

