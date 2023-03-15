#pragma once


//#include<iostream>
#include<string>
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
		
		// pair<int, int> getHumanMove(HexPlayer* currentPlayer, bool& run) override;
		
		pair<int, int> getHumanMove(HexGameEngine* hge) override; // {return pair<int, int>(-12,-14);}
		
		void badMoveMsg() override {
			cout << "ILLEGAL MOVE!\n";
		}
		
		/*void generateOutput(HexBoard& board, HexPlayer* winner, HexPlayer& human, HexPlayer& computer) override
		{
			cout << '\n'; drawHexBoard(board);
	
			if(winner == &human)
				cout << "\nHuman Wins\n";
	
			if(winner == &computer)
				cout << "\nComputer Wins\n";
		}*/
		
		void generateOutput(HexGameEngine* hge) override;
};

