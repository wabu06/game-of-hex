// HexGameApp initializes ui & drives game engine

#pragma once


#include<memory>

#include "HexGameEngine.h"
#include "HexConsoleUI.h"
#include "HexCurseUI.h"


using namespace std;

class HexGameApp
{
	static unique_ptr<HexGameApp> app;
	
	HexGameEngine hge;
	HexUI* ui;
	
	HexGameApp() = default;

		// the parseArgs method takes a command line in the form of: <hex "bs=9" "ui=curse"> as input,
		// and returns the user selected board size and user interface
		// improperly formed arguments are ignored, as well as incorrect parameters,
		// in either case defaults are used
	tuple<int, string> parseArgs(int len, char** args);

	int execute();

	public:
		HexGameApp(const HexGameApp& o_app) = delete;
	
		virtual ~HexGameApp() = default;

		//virtual ~HexGameApp()
		//{
			//if(ui != nullptr)
				//delete ui;
			
			//if(app != nullptr)
				//delete app;
		//}
		
		HexGameApp& operator=(const HexGameApp& o_app) = delete;
		
		static HexGameApp* getInstance()
		{
			if(app.get() == nullptr)
				//app = make_unique<HexGameApp>();
				app = unique_ptr<HexGameApp>(new HexGameApp());
			
			return app.get();
		}

		int initialize_and_execute(int argc , char** argv);
};

