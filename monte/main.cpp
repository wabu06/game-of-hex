//#include<numeric>

#include "HexGameEngine.h"


tuple<int, string> parseArgs(char* args[], int len);

int main (int argc, char* argv[])
{
	//HexGameEngine game, game1;
	
		// takes a command line in the form of: <hex "bs=9" "ui=curse"> as input,
		// and returns the user selected board size and user interface
		// improperly formed arguments are ignored, as well as incorrect parameters,
		// in either case defaults are used
	auto [bs, ui] = parseArgs(argv + 1, argc - 1); 
	
	HexGameEngine game(bs, ui), game1;
	
	return game.initialize().runLoop().shutdown();
}

tuple<int, string> parseArgs(char* args[], int len)
{
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

	int bSize{7}; string ui("curse");
	
	unordered_set<string> uiSet = {"console", "curse"};
	
	for(int i = 0; i < len; i++)
	{
		auto arg = string(args[i]);
		auto option = arg.substr(0, 3);
		auto param = arg.substr(3);
		
		for_each(option.begin(), option.end(), toLowerCase);
		auto opt = accumulate(option.begin(), option.end(), 0, sumchars);
		
		switch(opt)
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

