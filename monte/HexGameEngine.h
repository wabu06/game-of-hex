#pragma once


//#include<stdexcept>
#include<algorithm>
#include<random>
#include<chrono>
#include<unordered_set>
//#include<tuple>
#include<numeric>

//#include "HexPlayer.h"
//#include "HexBoard.h"

#ifndef CONSOLE
#include "HexConsoleUI.h"
#endif

#ifndef CURSE
#include "HexCurseUI.h"
#endif

#define MONTE 1

#if MONTE
#else
#include<tuple>
typedef tuple<int, int, vector<int>, unordered_map<int, hexColors> maxTuple;
#endif

class HexGameEngine
{
	HexPlayer computer, human, *currentPlayer, *winner;

	HexBoard board;
	HexUI* ui;
	
	bool isInitialized;
	bool done;
	
	int level;
	
	string UIname;

	bool isMoveLegal(int row, int col);

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

#if MONTE
	int genMonteMove(int shuffleMax = 1833);
#else
	maxTuple getMax(HexPlayer& maxPlayer, HexPlayer& minPlayer, HexBoard& maxBoard, vector<int> unColored, int move,
						unordered_map<int, hexColors> colored, bool max);
	int genMiniMaxMove();
#endif
	
	public:
		HexGameEngine(int size = 7, const string& uin = "console"): winner(nullptr), board( HexBoard(size) ), ui(nullptr), isInitialized(false),
																	done(false), level(3), UIname(uin) {}
		
		HexGameEngine(const HexGameEngine& hge): computer(hge.computer), human(hge.human), currentPlayer(hge.currentPlayer),
												 winner(hge.winner), board(hge.board), ui(hge.ui), isInitialized(hge.isInitialized),
												 done(hge.done), level(hge.level), UIname(hge.UIname) {}
		
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
			this->UIname = hge.UIname;
			
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

		HexGameEngine& initialize();
		
		HexGameEngine& runLoop()
		{
			if(!isInitialized) // insures initialize method is called first
				return *this;
	
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
			
			return *this;
		}
		
		int shutdown()
		{
			if(!isInitialized) {
				cerr << "\nGame Engine Was Not Initialized" << endl;
				return EXIT_FAILURE;
			}
				//ui->displayMsg("Game Engine Was Not Initialized");

			return EXIT_SUCCESS;
		}
};

