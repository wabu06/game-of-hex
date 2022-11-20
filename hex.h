#pragma once

#include<string>


using namespace std;

enum class hexColors: unsigned {NONE, RED, BLUE};

#ifndef _HEX

string toLowerCase(string txt)
{
	string lowTxt{};
	
	for(auto itr = txt.begin(); itr < txt.end(); itr++)
	{
		auto ch = static_cast<unsigned int>(*itr);
   	 
        if( (ch >= 65) && (ch <= 90) )
            lowTxt += static_cast<unsigned char>(ch+32);
        else
            lowTxt += *itr;
    }
    
    return lowTxt;
}

#endif

