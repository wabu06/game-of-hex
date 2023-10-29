//#include "HexGameEngine.h"
#include "HexGameApp.h"


int main(int argc, char* argv[]) {
	return HexGameApp::getInstance()->initialize_and_execute(argc, argv);
}
