#pragma once


#include<iostream>
//#include<string>
#include<utility>
//#include<algorithm>
#include<locale>
#include<unistd.h>
#include<termios.h>

#include "HexGameEngine.h"


class HexConsoleExe : public HexExecutor
{
	HexGameEngine hge;
	
	void drawHexBoard();
	
	public:
		HexConsoleExe(int bs = 7) : hge( HexGameEngine(bs, this) )
		{
			cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n";
			cout << "|A| |G|A|M|E| |O|F| |H|E|X|\n";
			cout << "+-+ +-+-+-+-+ +-+-+ +-+-+-+\n\n";
			
			cout << '\n'; drawHexBoard(); cout << '\n';
		}
		
		int getHumanPlayer() override;
		
		pair<int, int> getHumanMove() override;
		
		int execute() override
		{
			if( !hge.initialize() ) // insures initialize method is called first
				return hge.shutdown();

			if(hge.getComputer().getColor() == hexColors::BLUE)
			{
				hge.playComputer();
				updateUI();
			}

			bool done = hge.getDone();
			
			while(!done)
			{
				hge.playHuman();
				done = hge.getDone();
				
				if(hge.getWinner() != nullptr)
				{
					updateUI();
					break;
				}
				else if(done)
					break;
				else
					updateUI();
				
				hge.playComputer();
				updateUI();
				
				done = hge.getDone();
			}
			
			return hge.shutdown();
		}
		
		void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO) override {
			cout << '\n' << msg << '\n';
		}
		
		void updateUI() override
		{
			cout << '\n'; drawHexBoard();
	
			HexPlayer* winner = hge.getWinner();
	
			if(winner != nullptr)
				cout << '\n' << winner->getID() << " Wins, Game Over\n";
		}
};

