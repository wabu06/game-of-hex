//#include<numeric>

#include "HexGameEngine.h"


int main (int argc, char* argv[])
{
	//HexGameEngine game, game1;
	//auto [bs, ui] = parseArgs(argv + 1, argc - 1); 
	
	HexGameEngine game(argc, argv), game1;
	
	return game.run().shutdown();
}

