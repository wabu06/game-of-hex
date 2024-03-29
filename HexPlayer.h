#pragma once


#include<unordered_set>

#include "dPath.h"
#include "bfs.h"
#include "dfs.h"

#define _HEX

// 1. start with graph of unconnected nodes
// 2. everytime a node is colored, check for which neighbors are the same color
// 3. create an edge to every neighbor that is same color
// n = r*size + c

using namespace std;

enum class hexColors: unsigned {NONE, RED, BLUE};

class HexPlayer
{
	int bSize;
	
	hexColors color;
	graph playGraph;
	unordered_set<int> cellSet; // players current cells
	
	public:
		HexPlayer(hexColors c = hexColors::NONE, int size = 0): bSize(size), color(c), playGraph( graph{size*size} ),
																cellSet( unordered_set<int>{} ) {}
		
		hexColors getColor() { return color; }
		void setColor(hexColors c) { color = c; }
		
		graph getGraph() { return playGraph; }
		//dsPath& getPath() { return playPath; }
		
		int getCellCount() { return cellSet.size(); }
		void addCell(int c) { cellSet.insert(c); }

		int findPathSize(int c1, int c2)
		{
			dsPath playPath{playGraph};
			return playPath.getPathSize(c1, c2);
		}
		
		void connectCells(int c1, int c2) {
			playGraph.addEdge(c1, c2, 1);
		}
		
		vector<int> getCurrentCells(int start)
		{
			Bfs playBFS{bSize*bSize, playGraph};
			return playBFS.getCurrentCells(start);
		}
		
		unordered_set<int> getCurrentCells() { return cellSet; }
		
		bool hasPath(int c1, int c2)
		{
			Bfs playBFS{bSize*bSize, playGraph};
			return playBFS.hasPath(c1, c2);
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
			
			int slimit = bSize*bSize - bSize; int elimit = bSize*bSize;//int elimit = bSize*bSize + bSize;
			
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

