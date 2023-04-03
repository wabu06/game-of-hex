#pragma once


#include<utility>
#include<algorithm>
#include<locale>
#include<ncurses.h>
#include<csignal>

#include "HexUI.h"


using namespace std;


class HexCurseUI : public HexUI
{
	HexGameEngine* hge;

	static int rows, cols;
	
	WINDOW *mainwin, *boardWin, *banner, *inputWin, *msgWin;
	
	void drawHexBoard();
	
	public:
		HexCurseUI(HexGameEngine* engine);
		
		~HexCurseUI()
		{
			delwin(boardWin);
    		delwin(msgWin);
    		delwin(mainwin);
			endwin();
		}
		
		void finish(int sig)
		{
    		delwin(boardWin);
    		delwin(msgWin);
    		delwin(mainwin);
    		endwin();

    		exit(0);
		}
		
		static void resizeHandler(int sig);
		
		int getHumanPlayer() override
		{
			mvwprintw(msgWin, 6, 1, "1) Blue Player");
    		mvwprintw(msgWin, 7, 1, "2) Red Player");
			mvwprintw(msgWin, 8, 1, "==>Enter 1 or 2: ");
			wrefresh(msgWin);
			
			raw();
			
			int player = getch();
			
			while(player != 49 && player != 50) {
				mvwprintw(msgWin, 8, 1, "==>Invalid choice, Enter 1 or 2: ");
				wrefresh(msgWin);
				
				player = getch();
			}
			
			noraw();
			
			return player -= 48; 
		}
		
		pair<int, int> getHumanMove() override;

		void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO, bool replace = false) override
		{
			if(replace) // replace previous message
			{
				if(mType == MSGTYPE::INFO)
				{
					wmove(msgWin, rows - 3, 1);
					wclrtoeol(msgWin);
					mvwaddstr(msgWin, rows - 2, 1, msg.c_str() );
				}
			}
			else
			{
				if(mType == MSGTYPE::INFO)
				{
					char mstr[50];
					
					mvwinstr(msgWin, rows - 2, 1, mstr);
					wmove(msgWin, rows - 3, 1);
					wclrtoeol(msgWin);
					mvwaddstr(msgWin, rows - 3, 1, mstr);
					mvwaddstr(msgWin, rows - 2, 1, msg.c_str() );
				}
				
				if(mType == MSGTYPE::ERROR)
					mvwaddstr(msgWin, 5, 1, msg.c_str() );
			}
			
			wrefresh(msgWin);
		}
		
		void updateUI() override;
};

