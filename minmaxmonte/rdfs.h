#pragma once


#include<vector>

#include "graph.h"


using namespace std;

	// Depth First Search, can be used to find winner
class DFS
{
	vector<bool> visited; // first = visited, second = backtracked
	
	graph dfsGraph;
	
	void visitNodes(int n)
	{
		visited[n] = true;

		for(auto& N: dfsGraph.getNeighbors(n))
		{
			if( !visited[N] )
				visitNodes(N);
		}
	}
	
	public:
		DFS( const graph& G = graph() ): dfsGraph(G), visited( vector<bool>(dfsGraph.getNodeCount(), false) ) {}
		
		bool hasPath(int n1, int n2) {
			visitNodes(n1);
			return visited[n2];
		}
};

