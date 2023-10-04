//#include<numeric>

#include "HexGameEngine.h"


int main (int argc, char* argv[])
{
	//auto [bs, ui] = parseArgs(argv + 1, argc - 1); 
	
	HexGameEngine game(argc, argv), game1; game1(11, "console");
	
	return game.run().shutdown();
}

