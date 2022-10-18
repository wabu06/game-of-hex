#pragma once

#include "hex.h"

#include "dPath.h"

// 1. start with graph of unconnected nodes
// 2. everytime a node is colored, check for which neighbors are the same color
// 3. create an edge to every neighbor that is same color


class HexPlayer
{
	hexColors color;
	graph playerGraph;
	
	public:
		HexPlayer(hexColors c = hexColors::NONE, int size = 0): color(c), playerGraph( graph(size) ) {}
		
		hexColors getColor() { return color; }
		void setColor(hexColors c) { color = c; }
};

