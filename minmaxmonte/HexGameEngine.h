#pragma once


//#include<functional>


//using namespace std;

//enum class hexColors: unsigned {NONE, RED, BLUE};

//#ifndef HEX

//#include<stdexcept>
#include<algorithm>
#include<random>
#include<chrono>
#include<unordered_set>
#include<tuple>
#include<cmath>

#include<fstream>

#include "HexPlayer.h"
#include "HexBoard.h"

/*#ifndef CONSOLE*/
/*#include "HexConsoleUI.h"*/
/*#endif*/

/*#ifndef CURSE*/
/*#include "HexCurseUI.h"*/
/*#endif*/

extern enum class MSGTYPE: unsigned {INFO, WARN, ERROR};

extern class HexUI;

extern int HexUI::getHumanPlayer();
extern pair<int, int> HexUI::getHumanMove();
extern void HexUI::displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO);

struct GameState
{
	HexPlayer computer, human;
	HexBoard board;
	int cell, value;
	
	GameState& operator=(const GameState& hgs)
	{
		computer = hgs.computer;
		human = hgs.human;
		board = hgs.board;
		cell = hgs.cell;
		value = hgs.value;
		
		return *this;
	}
	
	bool operator==(const GameState& hgs) const {
		return cell == hgs.cell && value == hgs.value && &computer == &hgs.computer && &human == &hgs.human && &board == &hgs.board;
	}
};

template<>
struct hash<GameState>
{
	size_t operator() (GameState const& gs) const noexcept
	{
		hash<int> ptrHash;

		return ptrHash(gs.cell ^ gs.value ^ (long) &gs.computer ^ (long) &gs.human ^ (long) &gs.board);
	}
};

class HexGameEngine
{
	HexPlayer computer, human, *winner;
	
	HexUI* ui;

	HexBoard board;
	
	bool isInitialized;
	bool done;
	
	//int level; // game difficulty level
	
	random_device rd{"/dev/urandom"};

	ofstream fout;
	
	void(HexGameEngine::*playCurrentPlayer)();

	string algo; //= "monte";

	bool isMoveLegal(int row, int col);

	int(HexGameEngine::*generateMove)();

	int genMonteMove();

	GameState getMinMax(GameState hgs, int depth = -1, bool max = true, int alpha = 0);
	int genMiniMaxMove();

	public:
		HexGameEngine(int bs = 7) : winner(nullptr), ui(nullptr), board(HexBoard(bs)), isInitialized(false), done(true) {}
		
		HexGameEngine(const HexGameEngine& hge) : // copy constructor
			computer(hge.computer),
			human(hge.human),
			winner(hge.winner),
			ui(hge.ui),
			board(hge.board),
			isInitialized(hge.isInitialized),
			done(hge.done),
			rd(hge.rd),
			fout(hge.fout),
			algo(hge.algo) { generateMove = hge.generateMove; }
		
		HexGameEngine(const HexGameEngine&& hge) noexcept : // move constructor
			computer(hge.computer),
			human(hge.human),
			winner(hge.winner),
			ui(hge.ui),
			board(hge.board),
			isInitialized(hge.isInitialized),
			done(hge.done),
			rd(hge.rd),
			fout(hge.fout),
			algo(hge.algo) { if(hge.ui != nullptr) delete hge.ui; }
		
		~HexGameEngine() { if(ui != nullptr) delete ui; }

			// move assignment operator
		HexGameEngine& operator=(HexGameEngine&& hge) noexcept
		{
			if(this == &hge)
				return *this;
			
			this->computer = hge.computer;
			this->human = hge.human;
			this->winner = hge.winner;
			this->board = hge.board;
			this->ui = hge.ui;

			if(hge.ui != nullptr)
				delete hge.ui;

			this->isInitialized = hge.isInitialized;
			this->done = hge.done;
			this->rd = hge.rd;
			this->fout = hge.fout;
			this->algo = hge.algo;
	
			return *this;
		}
		
			// copy assignment operator
		HexGameEngine& operator=(const HexGameEngine& hge)
		{
			this->computer = hge.computer;
			this->human = hge.human;
			this->winner = hge.winner;
			this->board = hge.board;
			this->ui = hge.ui;
			this->isInitialized = hge.isInitialized;
			this->done = hge.done;
			this->rd = hge.rd;
			this->fout = hge.fout;
			this->algo = hge.algo;
			
			return *this;
		}
		
		HexUI* setUI(HexUI* ui) {
			this->ui = ui;
			return ui;
		}
		
		void playHuman();
		void playComputer();
		
		HexPlayer& getComputer() {
			return computer;
		}
		
		HexPlayer& getHuman() {
			return human;
		}
		
		HexPlayer* getWinner() {
			return winner;
		}

		HexBoard& getBoard() {
			return board;
		}
		
		bool getDone() {
			return done;
		}

		HexGameEngine& operator() (int bs = 7, string uin = "curse")
		{
			if(!done)
				throw string("\nERROR: Altering parameters not allowed while game is running!!\n");
			
			UIname = unordered_set<string>{"console", "curse"}.count(uin) == 1 ? uin : "curse";
			board = HexBoard(bs);
			
			return *this;
		}
		
		bool initialize(HexUI* ui = nullptr);

		/*HexGameEngine& run()
		{
			if( !initialize() ) // insures initialize method is called first
				return *this;

			while(!done)
			{
				try {
					(this->*playCurrentPlayer)();
				}
				catch(int exp) {
					done = true;
				}
				
				if( (winner == nullptr) && done )
					break;

				ui->updateUI();
			}
			
			return *this;
		}*/
		
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

//#endif

