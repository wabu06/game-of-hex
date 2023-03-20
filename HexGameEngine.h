#pragma once


//#include<iostream>
//#include<string>
//#include<stdexcept>
//#include<utility>
//#include<algorithm>
//#include<random>
//#include<locale>

//#include "HexPlayer.h"
#include "HexBoard.h"
#include "HexConsoleUI.h"


class HexGameEngine
{
	HexPlayer computer, human, *currentPlayer, *winner;
	HexBoard board;
	HexUI* ui;
	
	bool isInitialized;
	bool done;

	bool isMoveLegal(pair<int, int> move);

	void playHuman();
	void playComputer();

	pair<int, int> colorCellNeighbor(int cell);
	
	pair<int, int> findLongestPath(int cell);
	
	pair<int, int> extendLongestPath();
	
	public:
		HexGameEngine(int size = 7): winner(nullptr), board( HexBoard(size) ), ui(nullptr), isInitialized(false), done(false) {}

		HexPlayer& getComputer() {
			return computer;
		}
		
		HexPlayer& getHuman() {
			return human;
		}
		
		HexPlayer* getCurrentPlayer() {
			return currentPlayer;
		}
		
		void setCurrentPlayer(HexPlayer* p) {
			currentPlayer = p;
		}
		
		HexPlayer* getWinner() {
			return winner;
		}

		HexBoard& getBoard() {
			return board;
		}
		
		void setDone(bool d) {
			done = d;
		}
		
		void endGame() {
			done = true;
		}

		bool initialize();
		
		void runLoop()
		{
			if(!isInitialized) // insures initialize method is called first
				return;
	
			if(currentPlayer == &human)
				ui->updateUI(this);

			while(!done)
			{
				if(currentPlayer == &human)
					playHuman();
		
				if(currentPlayer == &computer)
					playComputer();
					
				if(done)
				{
					if(winner == nullptr) // if there's no winner, and done is true then exit
						ui->displayMsg("\nExiting ....\n");
					else
						ui->updateUI(this);
				}
				else
					ui->updateUI(this);
			}
		}
		
		void shutdown()
		{
			if(!isInitialized)
				ui->displayMsg("\nGame Engine Was Not Initialized\n");
	
			if(ui != nullptr)
				delete ui;
		}
};

