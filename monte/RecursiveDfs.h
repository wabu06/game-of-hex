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
		for(auto& N: dfsGraph.getNeighbors(n))
		{
			if( !visited[N] )
			{
				visited[N] = true;
				visitNodes(N);
			}
		}
		
		return;
	}
	
	public:
		Dfs( const graph& G = graph() ): dfsGraph(G) {
		
			auto size = dfsGraph.getNodeCount();
			
			visited = vector<bool>(size, false);
		}
		
		bool hasPath(int n1, int n2)
		{
			visited[n1] = true;
			visitNodes(n1);

			return visited[n2];
		}
};

