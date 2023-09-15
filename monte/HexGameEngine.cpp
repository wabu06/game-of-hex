#include "HexGameEngine.h"



tuple<int, string> HexGameEngine::parseArgs(int len, char* args[])
{
	if(len < 2)
		return {7, "curse"};

	auto sumchars = [](int s, const char& c) {
						return s + static_cast<unsigned int>(c);
					};
	
	auto toLowerCase = [](char& c) {
							c = tolower( c, locale("en_US.UTF8") );
						};
	
	auto digchk = [](const char& c)->bool {
							return isdigit(c, locale("en_US.UTF8"));
						};
	
	auto allDigits = [digchk](const string& arg)->bool {
							return all_of(arg.begin(), arg.end(), digchk);
						};

	len -= 1; args += 1;

	int bSize{7}; string ui("curse");
	
	unordered_set<string> uiSet = {"console", "curse"};
	
	for(int i = 0; i < len; i++)
	{
		auto arg = string(args[i]);
		
		if(arg.size() < 3)
			continue;
		
		auto option = arg.substr(0, 3);
		auto param = arg.substr(3);
		
		for_each(option.begin(), option.end(), toLowerCase);
		auto optv = accumulate(option.begin(), option.end(), 0, sumchars);
		
		switch(optv)
		{
			case 274: // bs=
				bSize = allDigits(param) ? stoi(param, nullptr) : 7;
			break;
			
			case 283: // ui=
				ui = uiSet.count(param) == 1 ? param : ui;
			break;
		}
	}

	return {bSize, ui};
}

void HexGameEngine::playHuman()
{
	bool legal;
	
	int row, col;
			
	do
	{	tie(row, col) = ui->getHumanMove();
	
		if( (row == 27) || (col == 32) )
		{
			done = true;
			return;
		}

		legal = isMoveLegal(row, col);
		
		if(!legal)
			ui->displayMsg("ILLEGAL MOVE!");
	}
	while(!legal);

	board.setCellColor( row, col, human.getColor() );
		
			// create edge between cell neighbors that are the same color
	int cell{ row*board.getSize() + col };
		
	vector<int> neighbors = board.getCellNeighbors(cell);
		
	for(auto& N: neighbors)
	{
		if( board.getCellColor(N) == human.getColor() )
			human.connectCells(cell, N);
	}

	ui->displayMsg("Human selects cell (" + to_string(row+1) + ", " + to_string(col+1) + ")");
	
	if( human.win() )
	{
		winner = &human;
		done = true;
		currentPlayer = nullptr;
	}
	else {
		currentPlayer = &computer; // human just played so computer plays next
		playCurrentPlayer = &HexGameEngine::playComputer;
	}
}

bool HexGameEngine::isMoveLegal(int row, int col)
{
	int size{ board.getSize() - 1 };
	
	bool inRange = (row >= 0) && (row <= size);
	
	inRange = (col >= 0) && (col <= size) && inRange;

	if(!inRange)
		return inRange;
	else
	{
		hexColors cc = board.getCellColor(row, col); // cell color

		return inRange && (cc == hexColors::NONE);
	}
	
}

bool HexGameEngine::initialize()
{
	auto sumchars = [](int s, const char& c) {
						return s + static_cast<unsigned int>(c);
					};

	auto opt = accumulate(UIname.begin(), UIname.end(), 0, sumchars);
	
	switch(opt)
	{
			case 755:
				ui = new HexConsoleUI(this); // user interface
			break;
			
			case 546:
				ui = new HexCurseUI(this);
			break;
	}
	
	isInitialized = true;
	done = false;

	//auto [player, ilevel] = ui->getHumanPlayer();
	
	auto player = ui->getHumanPlayer();
	
	if( player == (27 + 32) ) {
		done = true;
		isInitialized = false;
		return isInitialized;
	}
	
	generateMove = &HexGameEngine::genMonteMove;
	
	//level = ilevel;
	
	int size{ board.getSize() };
	
	if (player == 1)
	{
		human = HexPlayer(hexColors::BLUE, size, "Human");
		currentPlayer = &human;
		computer = HexPlayer(hexColors::RED, size, "Computer");
		playCurrentPlayer = &HexGameEngine::playHuman;
	}
	else
	{
		human = HexPlayer(hexColors::RED, size, "Human");
		computer = HexPlayer(hexColors::BLUE, size, "Computer");
		currentPlayer = &computer;
		playCurrentPlayer = &HexGameEngine::playComputer;
	}

	return isInitialized;
}

