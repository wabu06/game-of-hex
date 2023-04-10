#define _HEX

#include "HexGameEngine.h"


int main (int argc, char* argv[])
{
	HexGameEngine game, game1;
	
	if(argc > 1)
	{
		string arg1{argv[1]};
		
		bool allDigits = all_of(arg1.begin(), arg1.end(), [](char& c)->bool { return isdigit( c, locale("en_US.UTF8") ); });
		
		if(allDigits) {
			int bSize = stoi(arg1, nullptr);
			game = HexGameEngine(bSize);
		}
		else
			cerr << "\nInvalid Arguement, Using Default Board Size!" << endl;
	}
	
	if( !game.initialize() )
	{
		cerr << "\nGame Initialization Failure, Exiting ...." << endl;
		return EXIT_FAILURE;
	}

	game.runLoop();
	game.shutdown();
	
	return EXIT_SUCCESS;
}

