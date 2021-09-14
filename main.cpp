#include "hex.h"


int main ()
{
	hexGamePlay game{};
	
	int row, col; cout << Enter your move: "; cin >> row >> col;
	
	status result = game.analyzeMove(row, col);
	
	switch (result)
	{
		case status::ILLEGAL:
			break;
		case status::CONTINUE:
			break;
		case status::WINNER:
			break;
		default:
			return 0;
	}
	
	return 0;
}
