#pragma once


#include<iostream>

//#include "graph.h"
#include "hex.h"
//#include "bfs.h"
//#include "dfs.h"

//#include<string>

#include "HexPlayer.h"
#include "HexBoard.h"
//#include "HexUI.h"


class HexGameEngine
{
	HexPlayer computer, human, *currentPlayer;
	HexBoard board;
	//HexUI* ui;
	
	bool isInitialized;
	bool run; //stop
	
	void processInput()
	{
		char ans; 
		cout << "\nContinue game?(y/n) "; cin >> ans;
	
		if (ans != 'y') run = false;
	}
	
	void playHuman();
	void playComputer();
	
	void executeGamePlay()
	{
		if(currentPlayer == &human)
		{
			//generateOutput();
			playHuman();
			generateOutput();
			currentPlayer = &computer;
			playComputer();
			generateOutput();
			currentPlayer = &human;
			//return;
		}
		
		if(currentPlayer == &computer)
		{
			playComputer();
			currentPlayer = &human;
			generateOutput();
			playHuman();
			generateOutput();
			currentPlayer = &computer;
		}
	}
	
	void generateOutput();

	void colorCellNeighbor(int Cell);
	
	public:
		HexGameEngine(int size = 7): isInitialized(false), run(true), board( HexBoard(size) ) {}

		bool initialize();
		
		void runLoop() // or run()
		{
			if(!isInitialized)
				return;
		
			generateOutput();
			
			while(run)
			{
				executeGamePlay(); // update player graphs and gameBoard
				//generateOutput();
				processInput();
			}
		}
		
		void shutdown();
};

