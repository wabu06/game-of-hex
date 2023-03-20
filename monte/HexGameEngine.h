#pragma once


//#include<iostream>
//#include<string>
//#include<stdexcept>
//#include<utility>
#include<algorithm>
#include<random>
#include<chrono>
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
	
	void executeGamePlay()
	{
		if(currentPlayer == &human) {
			playHuman();
			return;
		}
		
		if(currentPlayer == &computer)
			playComputer();
	}

	int genMonteMove();
	
	public:
		HexGameEngine(int size = 7): winner(nullptr), board( HexBoard(size) ), ui(nullptr), isInitialized(false), done(false) {}
		
		HexGameEngine(HexGameEngine& hge): computer(hge.computer), human(hge.human), currentPlayer(hge.currentPlayer), winner(hge.winner),
										   board(hge.board), ui(hge.ui), isInitialized(hge.isInitialized), done(hge.done) {}

		HexGameEngine operator=(HexGameEngine&& hge)
		{
			this->computer = hge.computer;
			this->human = hge.human;
			this->currentPlayer = hge.currentPlayer;
			this->winner = hge.winner;
			this->board = hge.board;
			this->ui = hge.ui;
			this->isInitialized = hge.isInitialized;
			this->done = hge.done;
			
			return *this;
		}
		
		HexGameEngine operator=(HexGameEngine& hge)
		{
			this->computer = hge.computer;
			this->human = hge.human;
			this->currentPlayer = hge.currentPlayer;
			this->winner = hge.winner;
			this->board = hge.board;
			this->ui = hge.ui;
			this->isInitialized = hge.isInitialized;
			this->done = hge.done;
			
			return *this;
		}
		
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
				executeGamePlay(); // update player graphs and gameBoard
				
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
