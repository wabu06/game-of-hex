#pragma once


#include<utility>
#include<algorithm>
#include<locale>
#include<ncurses.h>
#include<csignal>
#include<cstring>

#include "HexUI.h"


using namespace std;

class HexCurseUI : public HexUI
{
	HexGameEngine* hge;
	
	static HexGameEngine* shge;

	static int rows, cols;
	
	char color[5]; // human color
	
	WINDOW *mainwin, *boardWin, *banner, *inputWin, *msgWin;
	
	void drawHexBoard();
	void showWinner(HexPlayer *winner);
	
	public:
		HexCurseUI(HexGameEngine* engine);
		
		~HexCurseUI()
		{
    		delwin(msgWin);
    		delwin(inputWin);
    		delwin(banner);
    		delwin(boardWin);
    		delwin(mainwin);
			endwin();
		}

		static void resize();
		
		static void sigHandler(int sig);
		
		int getHumanPlayer() override;
		
		pair<int, int> getHumanMove() override;

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

