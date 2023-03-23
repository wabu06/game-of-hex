#pragma once


#include<vector>
#include<queue>
#include<unordered_map>

//using namespace std;

#include "MinPQ.h"


class dsPath
{
	MinPQ openSet;
	graph spGraph;
	unordered_map<int, nodePath> closedSet;
			
		// Dijkstra's Algorithm is implemented here
	nodePath getNodePath(int sN, int dN);
	
	public:
			// constructor takes a graph object as input, and appropriately initializes the open and closed set
		dsPath( const graph& G /*= graph()*/ ): spGraph(G), openSet( MinPQ() ), closedSet( unordered_map<int, nodePath>{} ) {}
					
		 	// find shortest path between from node u to node w and returns the sequence of vertices representing shortest
			// path between them
		vector<int> getPath(int u, int w)
			{ nodePath snP = getNodePath(u, w); return snP.nodeList; }
		
			// returns the path cost associated with the shortest path between nodes u and w 
		int getPathSize(int u, int w)
			{ nodePath snP = getNodePath(u, w); return snP.ect; }
};
