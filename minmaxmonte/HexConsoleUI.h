#pragma once


#include<iostream>
//#include<string>
#include<utility>
//#include<algorithm>
#include<locale>
#include<unistd.h>
#include<termios.h>

#include "HexUI.h"


class HexConsoleUI : public HexUI
{

	HexBoard& ui_board;
	//HexPlayer* ui_winnner;
	
	void drawHexBoard();
	
	public:
		//HexConsoleUI() = default;
		
		HexConsoleUI(HexBoard& board) : ui_board(board)
		{
			cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n";
			cout << "|A| |G|A|M|E| |O|F| |H|E|X|\n";
			cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n\n";

			cout << '\n'; drawHexBoard(); cout << '\n';
		}

		~HexConsoleUI() = default;
		
		int getHumanPlayer() override;
		
		pair<int, int> getHumanMove() override;
		
		void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO) override {
			cout << '\n' << msg << '\n';
		}
		
		void updateUI(HexPlayer* winner) override
		{
			cout << '\n'; drawHexBoard();
	
			if(winner != nullptr)
				cout << '\n' << winner->getID() << " Wins, Game Over\n";
		}
};

