#pragma once


//#include<iostream>
//#include<string>
#include<utility>
//#include<algorithm>
#include<locale>
#include<unistd.h>
#include<termios.h>

#include "HexUI.h"


class HexConsoleUI : public HexUI
{
	HexGameEngine* hge;
	
	void drawHexBoard();
	
	public:
		HexConsoleUI(HexGameEngine* engine) : hge(engine)
		{
			cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n";
			cout << "|A| |G|A|M|E| |O|F| |H|E|X|\n";
			cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n\n";
			
			cout << '\n'; drawHexBoard(); cout << '\n';
		}
		
		int getHumanPlayer() override;
		
		pair<int, int> getHumanMove() override;
		
		void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO) override {
			cout << '\n' << msg << '\n';
		}
		
		void updateUI() override;
};

