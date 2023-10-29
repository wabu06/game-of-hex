#include "HexCurseUI.h"


int HexCurseUI::rows, HexCurseUI::cols;

//HexGameEngine *HexCurseUI::hge,
//HexGameEngine *HexCurseUI::curseHGE;

WINDOW *HexCurseUI::mainwin, *HexCurseUI::boardWin, *HexCurseUI::banner, *HexCurseUI::inputWin, *HexCurseUI::msgWin;

void HexCurseUI::resize()
{
	int nh, nw;

	getmaxyx(stdscr, nh, nw);
	resizeterm(nh, nw);

	rows = nh; cols = nw;
}

void HexCurseUI::finish()
{
	delwin(msgWin);
	delwin(inputWin);
	delwin(banner);
	delwin(boardWin);
	delwin(mainwin);
	endwin();
	
	exit(0);		
	//exit(curseHGE->shutdown());
}

void HexCurseUI::sigHandler(int sig)
{
	switch(sig)
	{
		case SIGTERM:
		case SIGINT:
			exit(0);
			//finish();
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

	int player;
	
	keypad(inputWin, TRUE); //raw();

	do
	{	mvwprintw(inputWin, rows/3 - 3, 1, "Enter 1 or 2: ");
		wrefresh(inputWin);

		player = wgetch(inputWin);
		
		if( (player == 27) || (player == 32) ) { // end program if <esc> or <spacebar> is pressed
			//finish();
			throw player; //return 27 + 32;
		}

		if(player != 49 && player != 50)
		{
			scroll(msgWin);
			mvwaddstr(msgWin, rows/2-1, 0, "INVALID ENTRY or CHOICE, Only Enter The Numbers 1 or 2!!");
			wrefresh(msgWin);
		}	
	}
	while(player != 49 && player != 50);
			
	keypad(inputWin, FALSE); //noraw();

	wclear(inputWin);
	
	char *cptr = player == 49 ? stpcpy(color, "Blue"): stpcpy(color, "Red");
	
	mvwprintw(inputWin, 1, 1, "Human Playing %s", color);
	
	box(inputWin, 0, 0);
	wrefresh(inputWin);

	return player - 48; 
}

HexCurseUI::HexCurseUI(HexBoard& board) : ui_board(board)
{
	//hge = new HexGameEngine(bs, this);
	//curseHGE = hge;
	
	mainwin = initscr();
	
	start_color();
	//init_pair(0, COLOR_WHITE, 0);
	init_pair(1, COLOR_BLUE, 0);
	init_pair(2, COLOR_RED, 0);
	
	getmaxyx(stdscr, rows, cols);
			
	int size = ui_board.getSize();
			
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
	wclear(inputWin);
	box(inputWin, 0, 0);
	mvwprintw(inputWin, 1, 1, "Human Playing %s", color);
	
	keypad(inputWin, TRUE);

	int row;
	bool digit;
	
	do
	{	mvwaddstr(inputWin, rows/3 - 3, 1, "Enter the row of your move: ");
		wrefresh(inputWin);
		
		row = wgetch(inputWin);
		
		if( (row == 27) || (row == 32) ) { // end program if <esc> or <spacebar> is pressed
			//finish();
			throw row; //return {27, 32};
		}

		digit = isdigit( (char) row, locale("en_US.UTF8") );
		
		if(!digit)
		{
			scroll(msgWin);
			mvwaddstr(msgWin, rows/2-1, 0, "INVALID ENTRY, Only Enter Digits!!");
			wrefresh(msgWin);
		}
	}
	while(!digit);

	int col;

	do
	{	mvwaddstr(inputWin, rows/3 - 3, 1, "Enter the column of your move: ");
		wrefresh(inputWin);
		
		col = wgetch(inputWin);
		
		if( (col == 27) || (col == 32) ) { // end program if <esc> or <spacebar> is pressed
			//finish();
			throw col; //return {27, 32};
		}
		
		digit = isdigit( (char) col, locale("en_US.UTF8") );
		
		if(!digit)
		{
			scroll(msgWin);
			mvwaddstr(msgWin, rows/2-1, 0, "INVALID ENTRY, Only Enter Digits!!");
			wrefresh(msgWin);
		}
	}
	while(!digit);

	keypad(inputWin, FALSE);

	return {row - 49, col - 49};
}

void HexCurseUI::drawHexBoard()
{
	int size{ ui_board.getSize() };
	
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
				switch( ui_board.getCellColor(r, cell) )
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
	char victor[11];
	stpcpy(victor, winner->getID().c_str() );
	
	int size = ui_board.getSize();

	int h = rows/6, w = (cols - (cols/2 + size))*3 / 4;
	int y = (rows - rows/6) / 2 - 1, x = cols/2 + size;
	
	flash();
	
	WINDOW* victorWin = newwin(h, w, y, x);
	refresh();

	mvwprintw(victorWin, (h - 2)/2, (w - 22)/2, "%s Wins, Game Over", victor);
	mvwprintw(victorWin, (h - 2)/2 + 1, (w - 25)/2, "Press Any Key To Continue");
	box(victorWin, 0, 0);

	wrefresh(victorWin);

	noecho();
	raw();
	
	wgetch(victorWin);

	noraw();
	echo();
	
	delwin(victorWin);
	finish();
}

void HexCurseUI::updateUI(HexPlayer *winner)
{
	drawHexBoard();
	
	if(winner != nullptr)
		showWinner(winner);
}

