#pragma once

//#include<utility>
#include<vector>
#include<stack>

#include "graph.h"

using namespace std;


	// Depth First Search, can be used to find winner
class Dfs
{
	vector<bool> visited; // first = visited, second = backtracked
	stack<int> dfsStack;
	
	graph dfsGraph;
	
	public:
		Dfs( graph G = graph() ): dfsGraph(G), dfsStack( stack<int>() )
		{
			auto size = dfsGraph.getNodeCount();
			
			visited = vector<bool>(size, false);
		}
		
		bool hasPath(int n1, int n2)
		{
			visited[n1] = true; auto currentNode = n1; bool found; //dfsStack.push(n1);
			
			do
			{	found = false;
				
					// check to see which neighbors of current node have not been visited
				for(auto& N: dfsGraph.getNeighbors(currentNode) )
				{
					if( !visited[N] )
					{
						visited[N] = true;
						dfsStack.push(N);
						currentNode = N;
						found = true;
						break;
					}
				}
					// if a neighbor of currentNode is found that has not been visited, mark it as visited,
					// and then check the neighbors of this newly found node
				if(found) 
					continue;
				
					// if all neighbors of current node has been visited, backtrack to it's parent, and check parent's neighbors
					// popping empty stack could case an error	
				dfsStack.pop(); currentNode = dfsStack.top();
				
			} while( !dfsStack.empty() );
			
			return visited[n2];
		}
};

