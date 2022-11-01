#pragma once


#include "dPath.h"
#include "bfs.h"
#include "dfs.h"
//#include "graph.h"
#include "hex.h"

// 1. start with graph of unconnected nodes
// 2. everytime a node is colored, check for which neighbors are the same color
// 3. create an edge to every neighbor that is same color
// n = r*size + c


class HexPlayer
{
	int pCell; // previously colored cell
	
	hexColors color;
	graph playGraph;
	dsPath playPath;
	//Bfs playBFS;
	
	int bSize;
	
	public:
		HexPlayer(hexColors c = hexColors::NONE, int size = 0): pCell(-1), color(c)
		{
			bSize = size;
			playGraph = graph{size*size};
			playPath = dsPath{playGraph}; // will need to implement the same as bfs
			//playBFS = Bfs{size*size, playGraph};
		}
		
		void setPrevCell(int pc) { pCell = pc; }
		int getPrevCell() { return pCell; }
		
		hexColors getColor() { return color; }
		void setColor(hexColors c) { color = c; }
		
		graph getGraph() { return playGraph; }
		dsPath getPath() { return playPath; }
		
		void connectCells(int c1, int c2) { playGraph.addEdge(c1, c2, 1); }
		
		bool win()
		{
			if( color == hexColors::BLUE )
				return blueWin();
			
			if( color == hexColors::RED )
				return redWin();
		}
		
		bool blueWin()
		{
			Bfs playBFS{bSize*bSize, playGraph};
			
			for(int start = 0; start < bSize; start++)
			{
				for(int end = (bSize - 1)*bSize; end < bSize*bSize; end++)
				{
						if( playBFS.hasPath(start, end) )
							return true;
				}
			}
			
			return false;
		}
		
		bool redWin()
		{
			Bfs playBFS{bSize*bSize, playGraph};
			
			int slimit = bSize*bSize - bSize; int elimit = bSize*bSize + bSize;
			
			for(int start = 0; start <= slimit; start += bSize)
			{
				for(int end = bSize - 1; end < elimit; end += bSize)
				{
						if( playBFS.hasPath(start, end) )
							return true;
				}
			}
			
			return false;
		}
};

