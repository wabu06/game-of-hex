// User Interface

#pragma once

#include<iostream>
#include<string>

//#include "HexBoard.h"

using namespace std;


enum class MSGTYPE: unsigned {INFO, WARN, ERROR};

class HexGameEngine;

class HexUI
{
	public:
		HexUI() = default; //{}
		virtual ~HexUI() = default; //{}
	
		//virtual pair<int, int> getHumanPlayer() = 0;
		virtual int getHumanPlayer() = 0;
		virtual pair<int, int> getHumanMove() = 0;
		virtual void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO) = 0;
		virtual void updateUI() = 0;
};

