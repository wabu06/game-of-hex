#include "HexGameEngine.h"


int main (int argc, char* argv[])
{
	HexGameEngine game(7), game1;
	
	//cout << argc;
	
	if( !game.initialize() )
	{
		cout << "Game Initialization Failure, exiting ...." << endl;
		return EXIT_FAILURE;
	}

	game.runLoop();
	game.shutdown();
	
	return EXIT_SUCCESS;
}

