#pragma once


#include "dPath.h"
#include "bfs.h"
#include "dfs.h"
//#include "graph.h"

#define _HEX
#include "hex.h"

// 1. start with graph of unconnected nodes
// 2. everytime a node is colored, check for which neighbors are the same color
// 3. create an edge to every neighbor that is same color
// n = r*size + c


class HexPlayer
{
	hexColors color;
	graph playGraph;
	//dsPath playPath;
	//Bfs playBFS;
	
	int bSize;
	
	public:
		HexPlayer(hexColors c = hexColors::NONE, int size = 0): color(c)
		{
			bSize = size;
			playGraph = graph{size*size};
			//playPath = dsPath{playGraph}; // will need to implement the same as bfs
			//playBFS = Bfs{size*size, playGraph};
		}
		
		hexColors getColor() { return color; }
		void setColor(hexColors c) { color = c; }
		
		graph getGraph() { return playGraph; }
		//dsPath& getPath() { return playPath; }
		
		int findPathSize(int c1, int c2)
		{
			dsPath playPath{playGraph};
			return playPath.getPathSize(c1, c2);
		}
		
		void connectCells(int c1, int c2)
		{ 
			if(color == hexColors::BLUE) // if cell 1 and 2 are in the same column, add edge weight as 2 instead of 1
			{
				auto col1 = c1 % bSize, col2 = c2 % bSize;
				
				if(col1 == col2)
					playGraph.addEdge(c1, c2, 2);
				else
					playGraph.addEdge(c1, c2, 1);
			}
			
			if(color == hexColors::RED) // if cell 1 and cell 2 are in the same row, add edge weight as 2 instead of 1
			{
				auto row1 = c1 / bSize, row2 = c2 / bSize;
				
				if(row1 == row2)
					playGraph.addEdge(c1, c2, 2);
				else
					playGraph.addEdge(c1, c2, 1);
			}
		}
		
		vector<int> getCurrentCells(int start)
		{
			Bfs playBFS{bSize*bSize, playGraph};
			return playBFS.getCurrentCells(start);
		}
		
		bool win()
		{
			bool pWin;

			if( color == hexColors::BLUE )
				pWin = blueWin();
			
			if( color == hexColors::RED )
				pWin = redWin();
			
			return pWin;
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

