// User Interface

#pragma once

#include "HexBoard.h"


class HexGameEngine;

class HexUI
{
	public:
		HexUI() {}
		virtual ~HexUI() {}
	
		virtual int getHumanPlayer() = 0;
		virtual pair<int, int> getHumanMove(HexGameEngine* hge) = 0;
		virtual void badMoveMsg() = 0;
		virtual void updateUI(HexGameEngine* hge) = 0;
};

