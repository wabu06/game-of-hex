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
	
	vector<int> closedSet;
	
	void visitNodes(int& start)
	{
		visited[start] = true; bfsQueue.push(start); int front;
			
		while( !bfsQueue.empty() )
		{
			front = bfsQueue.front(); closedSet.push_back(front); bfsQueue.pop();

			for(auto& N: bfsGraph.getNeighbors(front) )
			{
					if(visited[N])
						continue;
					
					bfsQueue.push(N);
					visited[N] = true;
			}
		}
	}
	
	public:
		//Bfs() = default;
		//Bfs( int size /*= 0*/, const graph& G /*= graph()*/ ): bfsGraph(G), bfsQueue( queue<int>() ), visited( vector<bool>(size, false) ) {}
		Bfs(int size, const graph& G): bfsGraph(G), bfsQueue( queue<int>() ), visited( vector<bool>(size, false) ), closedSet( vector<int>() ) {}
		
		bool hasPath(int n1, int n2)
		{
			visitNodes(n1);
			return visited[n2];
		}
		
		vector<int> getCurrentCells(int n)
		{
			visitNodes(n);
			return closedSet;
		}
};

