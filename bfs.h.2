#pragma once

#include<vector>
#include<queue>

#include "graph.h"

using namespace std;

	// Breath First Search, can be used to find winner
class Bfs
{
	vector<bool> visited;
	queue<int> bfsQueue;
	
	graph bfsGraph;
	
	public:
		//Bfs() {}
		Bfs( int size = 0, graph G = graph() ): bfsGraph(G), bfsQueue( queue<int>() ), visited( vector<bool>(size, false) ) {}
		
		bool hasPath(int n1, int n2)
		{
			visited[n1] = true; bfsQueue.push(n1); int front;
			
			while( !bfsQueue.empty() )
			{
				front = bfsQueue.front(); bfsQueue.pop();

				for(auto& N: bfsGraph.getNeighbors(front) )
				{
					if(visited[N])
						continue;
					
					bfsQueue.push(N);
					visited[N] = true;
				}
			}

			return visited[n2];
		}
};
