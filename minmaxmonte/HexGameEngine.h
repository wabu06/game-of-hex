#pragma once


//using namespace std;

#include<iostream>
#include<algorithm>
#include<random>
#include<chrono>
#include<unordered_set>
#include<tuple>
#include<cmath>

#include<fstream>

#include "HexBoard.h"
#include "HexPlayer.h"

#include "HexExecutor.h"
#include "HexConsoleExe.h"
#include "HexCurseExe.h"

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
	
	HexExecutor* exe;

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
		HexGameEngine(int bs = 5, HexExecutor* E = new HexConsoleExe() )
			:
		winner(nullptr), exe(E), board(HexBoard(bs)), isInitialized(false), done(true) {}
		
		HexGameEngine(const HexGameEngine& hge) : // copy constructor
			computer(hge.computer),
			human(hge.human),
			winner(hge.winner),
			exe(hge.exe),
			board(hge.board),
			isInitialized(hge.isInitialized),
			done(hge.done),
			//rd(hge.rd),
			//fout(hge.fout),
			algo(hge.algo) { generateMove = hge.generateMove; }
		
		HexGameEngine(HexGameEngine&& hge) noexcept : // move constructor
			computer(hge.computer),
			human(hge.human),
			winner(hge.winner),
			exe(hge.exe),
			board(hge.board),
			isInitialized(hge.isInitialized),
			done(hge.done),
			//rd(hge.rd),
			//fout(hge.fout),
			algo(hge.algo) { this->generateMove = hge.generateMove;
							 hge.winner = nullptr;
							 hge.exe = nullptr; }
		
		~HexGameEngine() { if(exe != nullptr) delete exe; }

			// move assignment operator
		HexGameEngine& operator=(HexGameEngine&& hge) noexcept
		{
			if(this == &hge)
				return *this;

			this->computer = hge.computer;
			this->human = hge.human;
			this->winner = hge.winner;
			hge.winner = nullptr;
			this->board = hge.board;
			this->exe = hge.exe;
			hge.exe = nullptr;
			this->isInitialized = hge.isInitialized;
			this->done = hge.done;
			//this->rd = hge.rd;
			//this->fout = hge.fout;
			this->algo = hge.algo;
			
			this->generateMove = hge.generateMove;
	
			return *this;
		}
		
			// copy assignment operator
		HexGameEngine& operator=(const HexGameEngine& hge)
		{
			this->computer = hge.computer;
			this->human = hge.human;
			this->winner = hge.winner;
			this->board = hge.board;
			this->exe = hge.exe;
			this->isInitialized = hge.isInitialized;
			this->done = hge.done;
			//this->rd = hge.rd;
			//this->fout = hge.fout;
			this->algo = hge.algo;
			
			this->generateMove = hge.generateMove;
			
			return *this;
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

		HexGameEngine& operator() (int bs = 7, HexExecutor* E = new HexConsoleExe())
		{
			if(!done)
				throw string("\nERROR: Altering parameters not allowed while game is running!!\n");

			board = HexBoard(bs);
			exe = E;
			
			return *this;
		}
		
		bool initialize();
		
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

