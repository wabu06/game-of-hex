#pragma once


#include<iostream>
#include<string>
#include<stdexcept>
#include<utility>
//#include<algorithm>
//#include<random>
#include<locale>

//#include "HexPlayer.h"
#include "HexBoard.h"
#include "HexUI.h"


using namespace std;

//namespace ui { enum class hexColors: unsigned {NONE, RED, BLUE}; }
//using namespace ui;

class HexConsoleUI : class HexUI
{
	drawHexBoard();
	
	public:
		HexConsoleUI()
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
		
		void badMoveMsg() override {
			cout << "ILLEGAL MOVE!\n";
		}
		
		void generateOutput() override
		{
			cout << '\n'; drawHexBoard();
	
			if(winner == &human)
				cout << "\nHuman Wins\n";
	
			if(winner == &computer)
				cout << "\nComputer Wins\n";
		}
};

