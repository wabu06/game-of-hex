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
	// pair<int, int> move;

	bool legal;
	
	int row, col;
			
	do
	{	tie(row, col) = ui->getHumanMove();
			
		if(done)
		{
			currentPlayer = nullptr;
			return; // end game if human choose to quit instead of entering a move
		}
			
		legal = isMoveLegal(row, col);
	}
	while(!legal);

	//int row{move.first}, col{move.second};
	
	board.setCellColor( row, col, human.getColor() ); //, human);
		
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
	else
		currentPlayer = &computer; // human just played so computer plays next
}

bool HexGameEngine::isMoveLegal(int row, int col)
{
	hexColors cc; // cell color
	
	int size{ board.getSize() - 1 };
	
	//int row{move.first}, col{move.second};

	if( row < 0 || row > size )
	{
		ui->displayMsg("ILLEGAL MOVE!");
		return false;
	}
		
	if( col < 0 || col > size )
	{
		ui->displayMsg("ILLEGAL MOVE!");
		return false;
	}
		
	cc = board.getCellColor(row, col);
		
	if(cc != hexColors::NONE)
	{
		ui->displayMsg("ILLEGAL MOVE!");
		return false;
	}

	return true;
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

	auto [player, ilevel] = ui->getHumanPlayer();
	
	level = ilevel;
	
	int size{ board.getSize() };
	
	if (player == 1)
	{
		human = HexPlayer(hexColors::BLUE, size);
		currentPlayer = &human;
		computer = HexPlayer(hexColors::RED, size);
	}
	else
	{
		human = HexPlayer(hexColors::RED, size);
		computer = HexPlayer(hexColors::BLUE, size);
		currentPlayer = &computer;
	}
	
	isInitialized = true;
	
	return isInitialized;
}

