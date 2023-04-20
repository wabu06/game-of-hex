#define CONSOLE

#include "HexGameEngine.h"


int HexCurseUI::rows; int HexCurseUI::cols;

HexGameEngine* HexCurseUI::shge;

void HexCurseUI::resize()
{
	int nh, nw;

	getmaxyx(stdscr, nh, nw);
	resizeterm(nh, nw);

	rows = nh; cols = nw;
}

void HexCurseUI::sigHandler(int sig)
{
	switch(sig)
	{
		case SIGTERM:
		case SIGINT:
			shge->shutdown();
			//exit(EXIT_SUCCESS);
		break;
		
		case SIGWINCH:
			resize();
		break;
	}
}

int HexCurseUI::getHumanPlayer()
{
	mvwprintw(inputWin, 1, 1, "1) Blue Player");
	mvwprintw(inputWin, 2, 1, "2) Red Player");
	mvwprintw(inputWin, 4, 1, "==>Enter 1 or 2: ");
	wrefresh(inputWin);
			
	raw();
			
	int player = wgetch(inputWin);
	wrefresh(inputWin);
			
	while(player != 49 && player != 50) {
		mvwprintw(inputWin, 4, 1, "==>Invalid choice, Enter 1 or 2: ");
		wrefresh(inputWin);

		player = wgetch(inputWin);
	}
			
	wclear(inputWin);
	mvwprintw(inputWin, 1, 1, "3) Expert");
	mvwprintw(inputWin, 2, 1, "2) Intermediate");
	mvwprintw(inputWin, 3, 1, "1) Beginner");
	mvwprintw(inputWin, 5, 1, "==>Enter 1, 2, or 3: ");
	box(inputWin, 0, 0);
	wrefresh(inputWin);

	int level = wgetch(inputWin);
	wrefresh(inputWin);
			
	while(level != 49 && level != 50 && level != 51) {
		mvwprintw(inputWin, 5, 1, "==>Invalid choice, Enter 1, 2, or 3: ");
		wrefresh(inputWin);

		level = wgetch(inputWin);
	}
			
	noraw();
			
	hge->setLevel(level - 48);
			
	wclear(inputWin);
	
	char *cptr = player == 49 ? stpcpy(color, "Blue"): stpcpy(color, "Red");
	
	mvwprintw(inputWin, 1, 1, "Human Playing %s", color);
	
	box(inputWin, 0, 0);
	wrefresh(inputWin);
			
	return player -= 48; 
}

HexCurseUI::HexCurseUI(HexGameEngine* engine) : hge(engine)
{
	shge = hge;
	
	mainwin = initscr();
	
	start_color();
	//init_pair(0, COLOR_WHITE, 0);
	init_pair(1, COLOR_BLUE, 0);
	init_pair(2, COLOR_RED, 0);
	
	getmaxyx(stdscr, rows, cols);
			
	int size = hge->getBoard().getSize();
			
	boardWin = newwin(rows, (cols/2 + size), 0, 0); //y, x
    refresh();
    box(boardWin, 0, 0);
    		
	drawHexBoard();
	
	int h = rows/6, w = cols - (cols/2 + size);
	
	int y = 0, x = cols/2 + size;
    		
    banner = newwin(h, w, y, x);
    refresh();
	box(banner, 0, 0);
    		
	mvwprintw(banner, 0, 0, "+-+ +-+-+-+-+ +-+-+ +-+-+-+");
	mvwprintw(banner, 1, 0, "|A| |G|A|M|E| |O|F| |H|E|X|");
	mvwprintw(banner, 2, 0, "+-+ +-+-+-+-+ +-+-+ +-+-+-+");
	wrefresh(banner);
	
	h = rows/3; //w = cols - (cols/2 + size);
	
	y = rows/6; x = cols/2 + size;
	
	inputWin = newwin(h, w, y, x);
    refresh();
	box(inputWin, 0, 0);
	
	h = rows/2; //w = cols - (cols/2 + size);
	
	y = rows/2; //x = cols/2 + size;
	
	msgWin = newwin(h, w, y, x);
	refresh();
	//box(msgWin, 0, 0);
	scrollok(msgWin, true);
	wrefresh(msgWin);
			
	signal(SIGWINCH, sigHandler);
	signal(SIGINT, sigHandler);
	signal(SIGTERM, sigHandler);
}

pair<int, int> HexCurseUI::getHumanMove()
{
	char input[20]; string cell;
	
	int row, col; //pair<int, int> position;
	
	nocbreak();
	
	wclear(inputWin);
	box(inputWin, 0, 0);
	mvwprintw(inputWin, 1, 1, "Human Playing %s", color);
	mvwaddstr(inputWin, rows/3 - 3, 1, "Enter your move, ");

	while(true)
	{
		//mvwaddstr(inputWin, rows/3 - 3, 1, "Enter your move, "); 
		mvwaddstr(inputWin, rows/3 - 2, 1, "Or Enter <h> for help, or <q> to quit: ");
		wrefresh(inputWin);
		wgetstr(inputWin, input);

		if(strlen(input) == 0) {
			scroll(msgWin);
			mvwaddstr(msgWin, rows/2-1, 0, "NO ENTRY MADE!");
			wrefresh(msgWin);
			wmove(inputWin, rows/3 - 2, 1);
			wclrtoeol(inputWin);
			box(inputWin, 0, 0);
			continue;
		}
		
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
				row = col = static_cast<unsigned int>('q') * static_cast<unsigned int>('Q');
				break;
			}
			
			if( (cell == "h") || (cell == "help") )
			{
				wclear(inputWin);
				mvwaddstr(inputWin, 1, 1, "If for example you want to select the cell at row 5,");
				mvwaddstr(inputWin, 2, 1, "& column 2, simply enter 52. Or if you wanted to");
				mvwaddstr(inputWin, 3, 1, "select the cell at row 7, & column 11, enter 0711.");
				mvwaddstr(inputWin, 5, 1, "Press Any Key To Continue");
				box(inputWin, 0, 0);
				wrefresh(inputWin);
				
				noecho();
				raw();
				
				wgetch(inputWin);
				
				noraw();
				echo();
				
				nocbreak();
				
				wclear(inputWin);
				box(inputWin, 0, 0);
				
				mvwprintw(inputWin, 1, 1, "Human Playing %s", color);
				mvwaddstr(inputWin, rows/3 - 3, 1, "Enter your move, ");

				continue;
			}
		}
		
		bool allDigits = all_of(cell.begin(), cell.end(), [](char& c) { return isdigit( c, locale("en_US.UTF8") ); });
		
		if(allDigits)
		{
			int number = stoi(cell, nullptr);
			
			if(cell.size() > 3)
			{
				row = number / 100 - 1;
				col = number % 100 - 1;
			}
			else
			{
				row = number / 10 - 1;
				col = number % 10 - 1;
			}
			
			break;
		}
		else
		{
			scroll(msgWin);
			mvwaddstr(msgWin, rows/2-1, 0, "INVALID ENTRY!");
			wrefresh(msgWin);
		}
		
		wmove(inputWin, rows/3 - 2, 1);
		wclrtoeol(inputWin);
		box(inputWin, 0, 0);
	}
	
	return {row, col}; //position;
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
						mvwaddch(boardWin, height, width, 'B' | COLOR_PAIR(1)); // cout << "B\u2650";
					break;
					
					case hexColors::RED:
						mvwaddch(boardWin, height, width, 'R' | COLOR_PAIR(2)); // cout << "R\u2648";
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

void HexCurseUI::showWinner(HexPlayer *winner)
{
	const char* victor = winner == &hge->getComputer() ? "Computer Wins" : "Human Wins";
	
	int size = hge->getBoard().getSize();

	int h = rows/6, w = (cols - (cols/2 + size))*3 / 4;
	int y = (rows - rows/6) / 2 - 1, x = cols/2 + size;
	
	flash();
	
	WINDOW* victorWin = newwin(h, w, y, x);
	refresh();

	mvwprintw(victorWin, (h - 2)/2, (w - 22)/2, "%s, Game Over", victor);
	mvwprintw(victorWin, (h - 2)/2 + 1, (w - 25)/2, "Press Any Key To Continue");
	box(victorWin, 0, 0);

	wrefresh(victorWin);

	noecho();
	raw();
	
	wgetch(victorWin);

	noraw();
	echo();
	
	delwin(victorWin);
}

void HexCurseUI::updateUI()
{
	drawHexBoard();
	
	HexPlayer *winner = hge->getWinner();
	
	if(winner != nullptr)
		showWinner(winner);

	//wrefresh(msgWin);
}

