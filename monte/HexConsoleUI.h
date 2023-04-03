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
	HexGameEngine* hge;
	
	void drawHexBoard();
	
	public:
		HexConsoleUI(HexGameEngine* engine) : hge(engine)
		{
			cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n";
			cout << "|A| |G|A|M|E| |O|F| |H|E|X|\n";
			cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n";
		}
		
		int getHumanPlayer() override
		{
			string player;
			
			do
			{	cout << "\n1) Blue Player\n2) Red Player\n" << "\u2016\nV==>Enter 1 or 2: ";
				getline(cin, player);
			}
			while( (player.size() > 1) || (player[0] != '1') && (player[0] != '2') );
			
			if (player[0] == '1')
				return 1;
			else
				return 2;
		}
		
		pair<int, int> getHumanMove() override;
		
		void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO, bool replace = false) override {
			cout << '\n' << msg << '\n';
		}
		
		void updateUI() override;
};

