#include "HexGameEngine.h"


int main (int argc, char* argv[])
{
	HexGameEngine game(11), game1;
	
	if( !game.initialize() )
	{
		cout << "Game Initialization Failure, exiting ...." << endl;
		return EXIT_FAILURE;
	}

	game.runLoop();
	game.shutdown();
	
	return EXIT_SUCCESS;
}

