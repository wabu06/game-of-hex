#pragma once


#define HEX

#include<functional>
#include<unordered_set>
#include<string>

//#include "HexGameEngine.h"

#include "dPath.h"
#include "bfs.h"
#include "dfs.h"
//#include "rdfs.h"

// 1. start with graph of unconnected nodes
// 2. everytime a node is colored, check for which neighbors are the same color
// 3. create an edge to every neighbor that is same color
// n = r*size + c

using namespace std;

//enum class hexColors: unsigned {NONE, RED, BLUE};

template<>
struct hash<hexColors>
{
	size_t operator() (hexColors const& hc) const noexcept
	{
		hash<int> cHash;

		return cHash(1 ^ 2 ^ 3);
	}
};

class HexPlayer
{
	int bSize;
	
	hexColors color;
	graph playGraph;
	
	string id;
	
	public:
		HexPlayer(hexColors c = hexColors::NONE, int size = 0, string nid = ""): bSize(size), color(c), playGraph( graph{size*size} ), id(nid) {}
		
		HexPlayer(const HexPlayer& player) : bSize(player.bSize), color(player.color), playGraph(player.playGraph), id(player.id) {}
		
		HexPlayer& operator=(const HexPlayer& player)
		{
			this->bSize = player.bSize;
			this->color = player.color;
			this->playGraph = player.playGraph;
			this->id = player.id;
			
			return *this;
		}
		
		HexPlayer& operator=(const HexPlayer&& player) noexcept // move assignment operator
		{
			if(this == &player)
				return *this;

			this->bSize = player.bSize;
			this->color = player.color;
			this->playGraph = player.playGraph;
			this->id = player.id;
			
			return *this;
		}
		
		string getID() {
			return id;
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
		
		void addCellNode(int c) {
			playGraph.addNode(c);
		}
		
		void connectCells(int c1, int c2) { 
			playGraph.addEdge(c1, c2, 1);
		}
		
		unordered_set<int> getCurrentCells(int start)
		{
			Bfs playBFS{bSize*bSize, playGraph};
			
			vector<int> cells = playBFS.getCurrentCells(start);
			
			return unordered_set<int>( cells.begin(), cells.end() );
		}
		
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
			
			int slimit = bSize*bSize - bSize; int elimit = bSize*bSize;
			
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
		
		vector<int> winPath()
		{
			vector<int> path;

			if( color == hexColors::BLUE )
				path = blueWinPath();
			
			if( color == hexColors::RED )
				path = redWinPath();
			
			return path;
		}
		
		vector<int> blueWinPath()
		{
			vector<int> path = vector<int>();
			
			dsPath dsp{playGraph};
			
			for(int start = 0; start < bSize; start++)
			{
				for(int end = (bSize - 1)*bSize; end < bSize*bSize; end++)
				{
						path = dsp.getPath(start, end);
						
						if(path.size() > 0)
							return path;
				}
			}
			
			return path;
		}
		
		vector<int> redWinPath()
		{
			vector<int> path = vector<int>();
			
			dsPath dsp{playGraph};
			
			int slimit = bSize*bSize - bSize; int elimit = bSize*bSize;
			
			for(int start = 0; start <= slimit; start += bSize)
			{
				for(int end = bSize - 1; end < elimit; end += bSize)
				{
						path = dsp.getPath(start, end);
						
						if(path.size() > 0)
							return path;
				}
			}
			
			return path;
		}
};

