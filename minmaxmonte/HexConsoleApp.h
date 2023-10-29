#pragma once


#include "HexGameApp.h"
#include "HexConsoleUI.h"


class HexConsoleApp : public HexGameApp
{
	public:
		HexConsoleAPP() = default;
		
		HexConsoleAPP(int bs)
		{
			HexBoard board(bs);
			ui = new HexConsoleUI(board);
			hge = HexGameEngine(bs);
		}
		
		virtual ~HexConsoleAPP() = default;
		
		int launch() override {
			return execute();
		}
}

