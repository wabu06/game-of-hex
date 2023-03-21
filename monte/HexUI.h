// User Interface

#pragma once

#include<string>

#include "HexBoard.h"


class HexGameEngine;

class HexUI
{
	public:
		HexUI() {}
		virtual ~HexUI() {}
	
		virtual int getHumanPlayer() = 0;
		virtual pair<int, int> getHumanMove(HexGameEngine* hge) = 0;
		virtual void displayMsg(const string& msg) = 0;
		virtual void updateUI(HexGameEngine* hge) = 0;
};

