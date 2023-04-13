#pragma once


//#include<stdexcept>
#include<algorithm>
#include<random>
#include<chrono>
#include<unordered_set>

//#include "HexPlayer.h"
//#include "HexBoard.h"

#ifndef CONSOLE
#include "HexConsoleUI.h"
#endif

#ifndef CURSE
#include "HexCurseUI.h"
#endif


class HexGameEngine
{
	HexPlayer computer, human, *currentPlayer, *winner;

	HexBoard board;
	HexUI* ui;
	
	bool isInitialized;
	bool done;
	
	int level;

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

	//int genMonteMove();
	int genMonteMove(int shuffleMax = 3600);
	
	public:
		HexGameEngine(const int& size = 7): winner(nullptr), board( HexBoard(size) ), ui(nullptr), isInitialized(false), done(false), level(3) {}
		
		HexGameEngine(const HexGameEngine& hge): computer(hge.computer), human(hge.human), currentPlayer(hge.currentPlayer),
												 winner(hge.winner), board(hge.board), ui(hge.ui), isInitialized(hge.isInitialized),
												 done(hge.done), level(hge.level) {}
		
		~HexGameEngine() {
			if(ui != nullptr)
				delete ui;
		}

		/*HexGameEngine operator=(HexGameEngine&& hge)
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
		}*/
		
		HexGameEngine& operator=(const HexGameEngine& hge)
		{
			this->computer = hge.computer;
			this->human = hge.human;
			this->currentPlayer = hge.currentPlayer;
			this->winner = hge.winner;
			this->board = hge.board;
			this->ui = hge.ui;
			this->isInitialized = hge.isInitialized;
			this->done = hge.done;
			this->level = hge.level;
			
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
		
		void setLevel(int L) {
			level = L;
		}

		bool initialize();
		
		void runLoop()
		{
			if(!isInitialized) // insures initialize method is called first
				return;
	
			if(currentPlayer == &human)
				ui->updateUI();

			while(!done)
			{
				executeGamePlay(); // update player graphs and gameBoard
				
				if(done)
				{
					if(winner == nullptr) // if there's no winner, and done is true then exit
						ui->displayMsg("Exiting ....");
					else
						ui->updateUI();
				}
				else
					ui->updateUI();
			}
		}
		
		void shutdown()
		{
			if(!isInitialized)
				cerr << "\nGame Engine Was Not Initialized" << endl;
				//ui->displayMsg("Game Engine Was Not Initialized");
		}
};

