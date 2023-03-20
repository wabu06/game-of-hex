#pragma once

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>

using namespace std;

#include "graph.h"
//#include "priorityQueue.h"

	// the "nodePath" class used to represent a list of nodes, corresponding
	// to a particular path and the total edge cost of that path
class nodePath
{
	public:
		int eNode; // end node
		int ect; // edge count total of a given node path
		vector<int> nodeList;

		nodePath( int N = -1, int T = 0, vector<int> NL = vector<int>() ): eNode(N), ect(T), nodeList(NL) {}
		nodePath( const nodePath& np): eNode(np.eNode), ect(np.ect), nodeList(np.nodeList) {}
		
		friend bool operator<(nodePath np1, nodePath np2) { return np1.ect < np2.ect; }
		friend bool operator>(nodePath np1, nodePath np2) { return np1.ect > np2.ect; }
};

class maxPQ
{
	priority_queue<nodePath> npq;
	unordered_map<int, nodePath> pqMap; // key = node

	public:
		maxPQ( priority_queue<nodePath> N = priority_queue<nodePath>{},
									unordered_map<int, nodePath> M = unordered_map<int, nodePath>{} ): npq(N), pqMap(M) {}

		bool notEmpty() { return !( npq.empty() && pqMap.empty() ); }
		
		bool contains(int node) { return pqMap.count(node) == 1; }
		
		nodePath getNodePath(int node) { return pqMap[node]; }
		
		void add(nodePath np)
		{
			pqMap[np.eNode] = np;
			npq.push(np);
		}

		nodePath remove(nodePath np)
		{
			vector<nodePath> npv = vector<nodePath>();
			nodePath top;
			bool found{false};
			
			while( !npq.empty() )
			{	
				top = npq.top();
				
				npq.pop();
				
				if(top.eNode == np.eNode)
				{
					found = true;
					break;
				}
				else
					npv.push_back(top);
			}
			
			//bool empty = npq.empty();
			
			if(found)
				pqMap.erase( top.eNode );
			
			for(auto& N: npv)
				npq.push(N);
			
			if(found)
				return top;
			else
				return nodePath();
		}
		
		void emptyPQ()
		{
			while( !npq.empty() ) { npq.pop(); }
			pqMap.clear();
		}
		
		nodePath getMax()
		{
			pqMap.erase( npq.top().eNode );
			nodePath top = npq.top();
			npq.pop();
			return top;
		}
		
		int qSize() { return npq.size(); }
		int mapSize() { return pqMap.size(); }
};


class dsPath
{
	maxPQ openSet;
	graph spGraph;
	unordered_map<int, nodePath> closedSet;
			
		// Dijkstra's Algorithm is implemented here
	nodePath getNodePath(int sN, int dN);
	
	public:
			// constructor takes a graph object as input, and appropriately initializes the open and closed set
		dsPath( graph G = graph() ): spGraph(G), openSet( maxPQ() ), closedSet( unordered_map<int, nodePath>{} ) {}
					
		 	// find shortest path between from node u to node w and returns the sequence of vertices representing shortest
			// path between them
		vector<int> getPath(int u, int w)
			{ nodePath snP = getNodePath(u, w); return snP.nodeList; }
		
			// returns the path cost associated with the shortest path between nodes u and w 
		int getPathSize(int u, int w)
			{ nodePath snP = getNodePath(u, w); return snP.ect; }
};
