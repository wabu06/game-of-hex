#pragma once


#include "HexUI.h"

using namespace std;

//enum class MSGTYPE: unsigned {INFO, WARN, ERROR};

class HexIO
{
	HexUI* ui;

	public:
		HexIO() = default;

		HexIO(HexUI* ui) {
			this->ui = ui;
		}

		virtual ~HexIO() = default;
		
		void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO) {
			ui->displayMsg(msg, mType);
		}
		
		int getHumanPlayer() {
			return ui->getHumanPlayer();
		}

		pair<int, int> getHumanMove() {
			return ui->getHumanMove();
		}

		void updateUI() {
			ui->updateUI();
		}
};

