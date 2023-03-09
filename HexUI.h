#pragma once


class HexUI
{
	public:
		HexUI() {}
	
		virtual int getHumanPlayer() {}
		virtual pair<int, int> getHumanMove() {}
		virtual void badMoveMsg() {}
		virtual void generateOutput() {}
};

