#include "hex.h"

#include<iostream>
#include<string>

using namespace std;


int main ()
{
	//hexGamePlay game{};
	
	//hCLR hc;
	
	string hc; bool ans{false};
	
	
	do {
		cout << "Red player or Blue player? "; cin >> hc;
		
		ans = hc == "B" || hc == "b" || hc == "blue" || hc == "Blue" || hc == "r" || hc == "R" || hc == "red" || hc == "Red";
	} while(!ans);
	
	//cout << hc << endl;
	
	game.setHumanColor(hc); //setBluePlayer()
	
	game.getCurrentBoard(); // then display it
	
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
