#define CONSOLE

#include "HexGameEngine.h"


int HexCurseUI::rows; int HexCurseUI::cols;

void HexCurseUI::resizeHandler(int sig)
{
	int nh, nw;

	getmaxyx(stdscr, nh, nw);
	resizeterm(nh, nw);

	rows = nh; cols = nw;
}

HexCurseUI::HexCurseUI(HexGameEngine* engine) : hge(engine)
{
	mainwin = initscr();
	getmaxyx(stdscr, rows, cols);
			
	int size = hge->getBoard().getSize();
			
	boardWin = newwin(rows, (cols/2 + size), 0, 0); //y, x
    refresh();
    box(boardWin, 0, 0);
    		
	drawHexBoard();
    		
    msgWin = newwin(rows, (cols - (cols/2 + size)), 0, (cols/2 + size));
    refresh();
	box(msgWin, 0, 0);
    		
	mvwprintw(msgWin, 1, 1, "+-+ +-+-+-+-+ +-+-+ +-+-+-+");
	mvwprintw(msgWin, 2, 1, "|A| |G|A|M|E| |O|F| |H|E|X|");
	mvwprintw(msgWin, 3, 1, "+-+ +-+-+-+-+ +-+-+ +-+-+-+");
			
	wrefresh(msgWin);
			
	signal(SIGWINCH, resizeHandler); //signal(SIGINT, finish); signal(SIGTERM, finish);
}

pair<int, int> HexCurseUI::getHumanMove()
{
	char input[20]; string cell;
	
	pair<int, int> position;
	
	nocbreak();

	while(true)
	{
		mvwaddstr(msgWin, 6, 1, "Enter selection for your move, <h> for help, or <q> to quit: ");
		wrefresh(msgWin);
		getstr(input);
		
		wmove(msgWin, 5, 1); // clear previous error message
		wclrtoeol(msgWin);
		wrefresh(msgWin);
		
		wmove(msgWin, 8, 1); // clear help message
		wclrtoeol(msgWin);
		wmove(msgWin, 9, 1);
		wclrtoeol(msgWin);
		wrefresh(msgWin);
		
		auto toLowerCase = [](char& c){ c = tolower( c, locale("en_US.UTF8") ); };
		
		cell = string(input);
	
		for_each(cell.begin(), cell.end(), toLowerCase);
		
		bool allAlpha = all_of(cell.begin(), cell.end(), [](char& c) { return isalpha( c, locale("en_US.UTF8") ); });
		
		if(allAlpha)
		{
			if( (cell == "q") || (cell == "quit") || (cell == "exit") || (cell == "end") )
			{
				hge->setCurrentPlayer(nullptr);
				hge->endGame();
				position.first = position.second = static_cast<unsigned int>('q') * static_cast<unsigned int>('Q');
				break;
			}
			
			if( (cell == "h") || (cell == "help") )
			{
				mvwaddstr(msgWin, 8, 1, "If for example you want to select the cell at row 5, & column 2, simply enter 52.");
				mvwaddstr(msgWin, 9, 1, "Or if you wanted to select the cell at row 7, & column 11, enter 0711.");
				wrefresh(msgWin);
				continue;
			}
		}
		
		bool allDigits = all_of(cell.begin(), cell.end(), [](char c) { return isdigit( c, locale("en_US.UTF8") ); });
		
		if(allDigits)
		{
			int number = stoi(cell, nullptr);
			
			if(cell.size() > 3)
			{
				position.first = number / 100 - 1;
				position.second = number % 100 - 1;
			}
			else
			{
				position.first = number / 10 - 1;
				position.second = number % 10 - 1;
			}
			
			break;
		}
		else {
			mvwaddstr(msgWin, 5, 1, "INVALID ENTRY");
			wrefresh(msgWin);
		}
			
	}
	
	return position;
}

void HexCurseUI::drawHexBoard()
{
	int size{ hge->getBoard().getSize() };
	
	int bRow{size}, width{10}, height{1}, cell;
	
	int slash;

	bool dot, back;
	
	for(int r = 0; r < bRow; r++)
	{
		cell = 0; dot = true;
		
		while(cell < bRow)
		{		
			if(dot)
			{
				switch( hge->getBoard().getCellColor(r, cell) )
				{
					case hexColors::BLUE:
						mvwprintw(boardWin, height, width, "B"); //cout << "B\u2650";
					break;
					
					case hexColors::RED:
						mvwprintw(boardWin, height, width, "R"); //cout << "R\u2648";
					break;
					
					default:
						mvwprintw(boardWin, height, width, ".");
				}
				dot = false;
				width++;
				cell++;
			}
			else {
				mvwprintw(boardWin, height, width, "---");
				width += 3;
				dot = true;
			}
		}
		
		if( r == (bRow-1) )
			continue;

		slash = 0; height++;
		
		width = height + 9;
		
		back = true;

		while(slash < bRow)
		{
			if(back) {
				mvwprintw(boardWin, height, width, "\\");
				back = false;
				width += 2;
				slash++;
			}
			else {
				mvwprintw(boardWin, height, width, "/");
				width += 2;
				back = true;
			}
		}

		height++; width = height + 9;
	}
	wrefresh(boardWin);
}

void HexCurseUI::updateUI()
{
	drawHexBoard();
	
	if( hge->getWinner() == &hge->getHuman() )
		mvwprintw(msgWin, rows - 2, 1, "Human Wins, Game Over");
	
	if( hge->getWinner() == &hge->getComputer() )
		mvwprintw(msgWin, rows - 2, 1, "Computer Wins, Game Over");

	wrefresh(msgWin);
}

