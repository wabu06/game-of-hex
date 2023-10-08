// User Interface

#pragma once

#include<iostream>
#include<string>

#include "HexGameEngine.h"


using namespace std;

enum class MSGTYPE: unsigned {INFO, WARN, ERROR};

//class HexGameEngine;

class HexUI
{
		// the parseArgs method takes a command line in the form of: <hex "bs=9" "ui=curse"> as input,
		// and returns the user selected board size and user interface
		// improperly formed arguments are ignored, as well as incorrect parameters,
		// in either case defaults are used
	static tuple<int, string> parseArgs(int len, char* args[]);

	public:
		HexUI() = default;
		virtual ~HexUI() = default;

		static HexUI* create(int argc = 1, char** argv = nullptr)
		{
			auto [bs, ui] = parseArgs(argc, argv);
			
			HexGameEngine hge(bs);
			
			if(ui == "console")
				return hge.setUI( new HexConsoleUI(hge) );
			else if(ui == "curse"")
				return hge.setUI( new HexCurseUI(hge) );
			else
				return nullptr;
		}
		
		virtual int runGame() = 0;

		virtual int getHumanPlayer() = 0;
		virtual pair<int, int> getHumanMove() = 0;
		virtual void displayMsg(const string& msg, MSGTYPE mType = MSGTYPE::INFO) = 0;
		virtual void updateUI() = 0;
};

tuple<int, string> HexUI::parseArgs(int len, char* args[])
{
	if(len < 2)
		return {7, "curse"};
	
	auto toLowerCase = [](char& c) { c = tolower( c, locale("en_US.UTF8") ); };
	
	auto digchk = [](const char& c)->bool { return isdigit(c, locale("en_US.UTF8")); };
	
	auto allDigits = [digchk](const string& arg)->bool { return all_of(arg.begin(), arg.end(), digchk); };

	len -= 1; args += 1;

	int bs{7}; string ui("curse");
	
	unordered_set<string> uiType = {"console", "curse"};
	
	auto argc = 0;
	
	for(int i = 0; i < len || argc < 2; i++)
	{
		auto arg = string(args[i]);
		
		if(arg.size() < 3)
			continue;
		
		auto option = arg.substr(0, 3);
		auto value = arg.substr(3);
		
		for_each(option.begin(), option.end(), toLowerCase);
		for_each(value.begin(), value.end(), toLowerCase);
		
		if(option == "ui")
		{
			if(uiType.count(value) == 1) {
				ui = value;
				++argc;
			}
		}
		else if(option == "bs")
		{
			if(allDigits(value)) {
				bs = stoi(value, nullptr);
				++argc;
			}
		}
	}

	return {bs, ui};
}

