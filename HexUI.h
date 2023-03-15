#pragma once

#include "HexBoard.h"


class HexGameEngine;

class HexUI
{
	public:
		HexUI() {}
	
		virtual int getHumanPlayer() { return -1; }
		//virtual pair<int, int> getHumanMove(HexPlayer* currentPlayer, bool& run) { return pair{-1, -1}; }
		virtual pair<int, int> getHumanMove(HexGameEngine* hge) { return pair<int, int>(-1,-1); }
		virtual void badMoveMsg() {}
		//virtual void generateOutput(HexBoard& board, HexPlayer* winner, HexPlayer& human, HexPlayer& computer) {}
		virtual void generateOutput(HexGameEngine* hge) {}
};

