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
	mainwin = initscr();
	getmaxyx(stdscr, rows, cols);
			
	int size = hge->getBoard().getSize();
			
	boardWin = newwin(rows, (cols/2 + size), 0, 0); //y, x
    refresh();
    box(boardWin, 0, 0);
    		
	drawHexBoard();
    		
    banner = newwin(rows/6, (cols - (cols/2 + size)), 0, (cols/2 + size));
    refresh();
	box(banner, 0, 0);
    		
	mvwprintw(banner, 0, 0, "+-+ +-+-+-+-+ +-+-+ +-+-+-+");
	mvwprintw(banner, 1, 0, "|A| |G|A|M|E| |O|F| |H|E|X|");
	mvwprintw(banner, 2, 0, "+-+ +-+-+-+-+ +-+-+ +-+-+-+");
	wrefresh(banner);
	
	inputWin = newwin(rows/3, (cols - (cols/2 + size)), rows/6, (cols/2 + size));
    refresh();
	box(inputWin, 0, 0);
	
	msgWin = newwin(rows/2, (cols - (cols/2 + size)), rows/2, (cols/2 + size));
	refresh();
	//box(msgWin, 0, 0);
	scrollok(msgWin, true);
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
		mvwaddstr(inputWin, rows/3 - 3, 1, "Enter your move, "); 
		mvwaddstr(inputWin, rows/3 - 2, 1, "Or Enter <h> for help, or <q> to quit: ");
		wrefresh(inputWin);
		wgetstr(inputWin, input);
		
		wclear(inputWin);
		mvwprintw(inputWin, 1, 1, "Human Playing %s", color);
		box(inputWin, 0, 0);
		
		//wmove(inputWin, 5, 1); // clear previous error message
		//wclrtoeol(inputWin);
		//wrefresh(inputWin);
		
		//wmove(inputWin, 8, 1); // clear help message
		//wclrtoeol(inputWin);
		//wmove(inputWin, 9, 1);
		//wclrtoeol(inputWin);
		//wrefresh(inputWin);
		
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
				
				mvwprintw(inputWin, 1, 1, "Human Playing %s", color);
				box(inputWin, 0, 0);
				
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
		else
		{
			scroll(msgWin);
			mvwaddstr(msgWin, rows/2-2, 1, "INVALID ENTRY");
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

void HexCurseUI::showWinner(const string& msg)
{
	noecho();
	raw();

	scroll(msgWin);
	mvwprintw(msgWin, rows/2-2, 1, "%s, Game Over", msg.c_str());
	scroll(msgWin);
	mvwprintw(msgWin, rows/2-2, 1, "Press Any Key To Continue");

	box(msgWin, 0, 0);
	wrefresh(msgWin);

	wgetch(msgWin);

	noraw();
	echo();
}

void HexCurseUI::updateUI()
{
	drawHexBoard();
	
	if( hge->getWinner() == &hge->getHuman() )
		showWinner("Human Wins");
	
	if( hge->getWinner() == &hge->getComputer() )
		showWinner("Computer Wins");

	wrefresh(msgWin);
}

