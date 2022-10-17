#include "graph.h"

class HexPlayer
{
	hexColors color;
	graph playerGraph;
	
	public:
		HexPlayer(hexColors c): color(c), playerGraph( graph() ) {}
		
		hexColors getColor() { return color; }
		void setColor(hexColors c) { color = c; }
};

