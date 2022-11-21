#pragma once


#include<iostream>
//#include<string>
#include<stdexcept>
#include<utility>
#include<algorithm>

//#include "graph.h"
//#include "hex.h"
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
	
	//ComputerPlayer* CP = new ComputerPlayerLP(board, computer); // use smart pointer
	
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
	
	void drawHexBoard();
	
	void generateOutput();

	pair<int, int> colorCellNeighbor(int Cell);
	pair<int, int> colorCellNeighbor(int bCell, int eCell);
	
	public:
		HexGameEngine(int size = 7): winner(nullptr), board( HexBoard(size) ), isInitialized(false), run(true) {}

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

