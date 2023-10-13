// User Interface, will drive/execute game engine

#pragma once

//#include<iostream>
//#include<algorithm>
//#include<locale>
#include<string>
#include<utility>
//#include<unordered_set>


using namespace std;

enum class MSGTYPE: unsigned {INFO, WARN, ERROR};

class HexGameEngine;

class HexExecutor
{
		// the parseArgs method takes a command line in the form of: <hex "bs=9" "ui=curse"> as input,
		// and returns the user selected board size and user interface
		// improperly formed arguments are ignored, as well as incorrect parameters,
		// in either case defaults are used
	static tuple<int, string> parseArgs(int len, char** args);

	protected:
		HexGameEngine* hge;

	public:
		HexExecutor() = default;
		virtual ~HexExecutor() = default;

		static HexExecutor* create(int argc , char** argv);
		
		//virtual int execute() = 0;
		int execute();

		virtual int getHumanPlayer() = 0;
		virtual pair<int, int> getHumanMove() = 0;
		virtual void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO) = 0;
		virtual void updateUI() = 0;
};

