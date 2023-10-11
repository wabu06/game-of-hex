#pragma once


#include<utility>
//#include<algorithm>
#include<locale>
#include<ncurses.h>
#include<csignal>
#include<cstring>

#include "HexGameEngine.h"


class HexCurseExe : public HexExecutor
{
	static HexGameEngine hge;

	static int rows, cols;
	
	char color[5]; // human color
	
	static WINDOW *mainwin, *boardWin, *banner, *inputWin, *msgWin;
	
	void drawHexBoard();
	void showWinner(HexPlayer *winner);
	
	public:
		HexCurseExe(int bs = 7);
		
		~HexCurseExe()
		{
    		delwin(msgWin);
    		delwin(inputWin);
    		delwin(banner);
    		delwin(boardWin);
    		delwin(mainwin);
			endwin();
		}

		static void sigHandler(int sig);
		
		static void resize();
		
		static void finish();

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
				
				//if( (winner == nullptr) && done )
					//break;
			}
			
			return hge.shutdown();
		}

		void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO) override
		{	
			if(mType == MSGTYPE::INFO)
			{
				scroll(msgWin);
				mvwprintw(msgWin, rows/2-1, 0, "%s", msg.c_str());
				wrefresh(msgWin);
			}

			if(mType == MSGTYPE::ERROR) {
				mvwprintw(inputWin, 1, 1, "%s", msg.c_str());
				wrefresh(inputWin);
			}
		}
		
		void updateUI() override;
};

