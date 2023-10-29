#include "HexGameApp.h"


unique_ptr<HexGameApp> HexGameApp::app; //= nullptr;

int HexGameApp::initialize_and_execute(int argc, char** argv)
{
	auto [bs, ui] = parseArgs(argc, argv);

	hge = HexGameEngine(bs);

	if(ui == "console") {
		this->ui = new HexConsoleUI(hge.getBoard());
		//return execute();
	}
	else if(ui == "curse") {
		this->ui = new HexCurseUI(hge.getBoard());
		//return execute();
	}
	else {
		this->ui = new HexConsoleUI(hge.getBoard());
		//return execute();
	}
	
	return execute();
}

int HexGameApp::execute()
{
	if( !hge.initialize(this->ui) ) // insures initialize method is called first
		return hge.shutdown();

	if(hge.getComputer().getColor() == hexColors::BLUE)
	{
		hge.playComputer();
		ui->updateUI(hge.getWinner());
	}

	bool done = hge.getDone();
			
	while(!done)
	{
		hge.playHuman();
		done = hge.getDone();
		HexPlayer* winner = hge.getWinner();
				
		if(winner != nullptr)
		{
			ui->updateUI(winner);
			break;
		}
		else if(done)
			break;
		else
			ui->updateUI(winner);
				
		hge.playComputer();
		ui->updateUI(hge.getWinner());
				
		done = hge.getDone();
	}
			
	return hge.shutdown();
}

tuple<int, string> HexGameApp::parseArgs(int len, char** args)
{
	if(len < 2)
		return {7, "curse"};

	auto toLowerCase = [](char& c) { c = tolower( c, locale("en_US.UTF8") ); };
	
	auto digchk = [](const char& c)->bool { return isdigit(c, locale("en_US.UTF8")); };
	
	auto allDigits = [digchk](const string& arg)->bool { return all_of(arg.begin(), arg.end(), digchk); };

	len -= 1;
	args += 1;

	int bs{7}; string ui("curse");
	
	unordered_set<string> uiType = {"console", "curse"};
	
	auto argc = 0;
	
	for(int i = 0; i < len && argc < 2; i++)
	{
		auto arg = string(args[i]);

		if(arg.size() < 3)
			continue;
		
		auto option = arg.substr(0, 2);
		auto value = arg.substr(3);

		for_each(option.begin(), option.end(), toLowerCase);
		for_each(value.begin(), value.end(), toLowerCase);

		if(option == "ui")
		{
			if(uiType.count(value) == 1) {
				ui = value;
				++argc;
			}
		}
		else if(option == "bs")
		{
			if(allDigits(value)) {
				bs = stoi(value, nullptr);
				++argc;
			}
		}
	}

	return {bs, ui};
}

