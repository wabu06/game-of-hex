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

	static int rows, cols;
	
	char color[5];
	
	WINDOW *mainwin, *boardWin, *banner, *inputWin, *msgWin;
	
	void drawHexBoard();
	void showWinner(const string& msg);
	
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
		
		void finish(int sig)
		{
    		delwin(msgWin);
    		delwin(inputWin);
    		delwin(banner);
    		delwin(boardWin);
    		delwin(mainwin);
    		endwin();

    		exit(0);
		}
		
		static void resizeHandler(int sig);
		
		int getHumanPlayer() override;
		
		pair<int, int> getHumanMove() override;

		void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO) override
		{
			//char txt[50];
			
			if(mType == MSGTYPE::INFO)
			{
				//wmove(msgWin, rows/2-2, 1);
				//winstr(msgWin, txt);
				scroll(msgWin);
				//wmove(msgWin, rows/2-3, 1);
				//wclrtoeol(msgWin);
				//mvwprintw(msgWin, rows/2-3, 1, "%s", txt);
				mvwprintw(msgWin, rows/2-2, 1, "%s", msg.c_str());
				//wprintw(msgWin, "%s", msg.c_str());
				//box(msgWin, 0, 0);
				wrefresh(msgWin);
			}

			if(mType == MSGTYPE::ERROR) {
				mvwprintw(inputWin, 1, 1, "%s", msg.c_str());
				//box(inputWin, 0, 0);
				wrefresh(inputWin);
			}
		}
		
		void updateUI() override;
};

