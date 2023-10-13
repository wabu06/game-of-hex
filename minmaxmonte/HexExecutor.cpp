#include "HexGameEngine.h"



HexExecutor* HexExecutor::create(int argc, char** argv)
{
	auto [bs, ui] = parseArgs(argc, argv);

	if(ui == "console")
		return new HexConsoleExe(bs);
	else if(ui == "curse")
		return new HexCurseExe(bs);
	else
		return new HexConsoleExe(3);
}

tuple<int, string> HexExecutor::parseArgs(int len, char** args)
{
	if(len < 2)
		return {7, "curse"};

	auto toLowerCase = [](char& c) { c = tolower( c, locale("en_US.UTF8") ); };
	
	auto digchk = [](const char& c)->bool { return isdigit(c, locale("en_US.UTF8")); };
	
	auto allDigits = [digchk](const string& arg)->bool { return all_of(arg.begin(), arg.end(), digchk); };

	len -= 1;
	args += 1;

	int bs{7}; string ui("curse");
	
	unordered_set<string> uiType = {"console", "curse"};
	
	auto argc = 0;
	
	for(int i = 0; i < len && argc < 2; i++)
	{
		auto arg = string(args[i]);

		if(arg.size() < 3)
			continue;
		
		auto option = arg.substr(0, 2);
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

