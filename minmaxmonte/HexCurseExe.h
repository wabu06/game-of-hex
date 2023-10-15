#pragma once


#include<utility>
//#include<algorithm>
#include<locale>
#include<ncurses.h>
#include<csignal>
#include<cstring>


class HexGameEngine;

class HexCurseExe : public HexExecutor
{
	//static HexGameEngine* hge;
	static HexGameEngine* curseHGE;

	static int rows, cols;
	
	char color[5]; // human color
	
	static WINDOW *mainwin, *boardWin, *banner, *inputWin, *msgWin;
	
	void drawHexBoard();
	void showWinner(HexPlayer *winner);
	
	public:
		HexCurseExe() = default;
		HexCurseExe(int bs);
		
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
		
		//int execute() override;
		int launch() override {
			return execute();
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
