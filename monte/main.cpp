#define _HEX

#include "HexGameEngine.h"


int main (int argc, char* argv[])
{
	HexGameEngine game, game1;
	
	if(argc > 1)
	{
		try
		{
			string arg1{argv[1]};
			
			size_t cc; int bSize = stoi(arg1, &cc);
			
			if( (cc == 0) || (cc != arg1.size()) )
				throw invalid_argument("not all characters were digits");
			
			game = HexGameEngine{bSize};
		}
		catch(exception const& exp) {}
	}
	
	if( !game.initialize() )
	{
		cout << "Game Initialization Failure, exiting ...." << endl;
		return EXIT_FAILURE;
	}

	game.runLoop();
	game.shutdown();
	
	return EXIT_SUCCESS;
}

