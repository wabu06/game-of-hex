#include "HexGameEngine.h"
//#include "HexExecutor.h"


int main(int argc, char* argv[]) {
	return HexExecutor::create(argc, argv)->execute();
}
