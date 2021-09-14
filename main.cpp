#include "hex.h"


int main ()
{
	hexGamePlay game{};
	
	int row, col; cout << Enter your move: "; cin >> row >> col;
	
	move = game.getMove(row, col);
	
	switch (move)
	{
		case illegal:
			break;
		case continue:
			break;
		case winner:
			break;
		default:
			return 0;
	}
	
	return 0;
}
