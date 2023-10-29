#pragma once

//#include<iostream>
//#include<algorithm>
//#include<locale>
#include<string>
#include<utility>

#include "HexBoard.h"
#include "HexPlayer.h"


using namespace std;

enum class MSGTYPE: unsigned {INFO, WARN, ERROR};

class HexUI
{
	public:
		HexUI() = default;
		virtual ~HexUI() = default;

		virtual int getHumanPlayer() = 0;
		virtual pair<int, int> getHumanMove() = 0;
		virtual void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO) = 0;
		virtual void updateUI(HexPlayer* winner) = 0;
};

