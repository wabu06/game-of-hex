#pragma once


#include<iostream>
//#include<string>
#include<utility>
#include<algorithm>
#include<locale>

#include "HexUI.h"


using namespace std;


class HexConsoleUI : public HexUI
{
	void drawHexBoard(HexBoard& board);
	
	public:
		HexConsoleUI()
		{
			cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n";
			cout << "|A| |G|A|M|E| |O|F| |H|E|X|\n";
			cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n";
		}
		
		int getHumanPlayer() override;
		
		pair<int, int> getHumanMove(HexGameEngine* hge) override;

		void displayMsg(string&& msg) override {
			cout << msg;
		}
		
		void updateUI(HexGameEngine* hge) override;
};

