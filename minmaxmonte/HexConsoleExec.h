#pragma once


#include<iostream>
//#include<string>
#include<utility>
//#include<algorithm>
#include<locale>
#include<unistd.h>
#include<termios.h>


class HexGameEngine;

class HexConsoleExe : public HexExecutor
{
	//HexGameEngine* hge;
	
	void drawHexBoard();
	
	public:
		HexConsoleExe() = default;
		HexConsoleExe(int bs);
		~HexConsoleExe() = default;
		
		int getHumanPlayer() override;
		
		pair<int, int> getHumanMove() override;
		
		//int execute() override;
		int launch() override {
			return execute();
		}
		
		void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO) override {
			cout << '\n' << msg << '\n';
		}
		
		void updateUI() override;
};

