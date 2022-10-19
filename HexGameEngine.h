#pragma once


#include<iostream>

#include "hex.h"

//#include<string>

#include "HexPlayer.h"
#include "HexBoard.h"
//#include "HexUI.h"

//using std namespace;

//enum class hexColors: unsigned {NONE, RED, BLUE};

class HexGameEngine
{
	int row, col; // row & col chosen by human player
	//int cRow, cCol; // row & col chosen by computer

	HexPlayer computer, human, *currentPlayer;
	HexBoard board;
	//HexUI* ui;
	
	bool isInitialized;
	bool run; //stop
	
	void processInput();
	void updateGame();
	void generateOutput();
	
	public:
		HexGameEngine(int size = 7): isInitialized(false), run(true), board( HexBoard(size) ) {}

		bool initialize();
		void runLoop(); // or run()
		void shutdown();
};

