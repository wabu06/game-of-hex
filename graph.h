#pragma once

#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;


class edge
{
	public:
		int node; // vertex endpoint of an edge
		int weight; // edge weight (distance)
		
		edge(int N = -1, int W = 0): node(N), weight(W){}
};

class graph
{
	int size; // current graph size (amount of nodes/vertices)
	
		// graph implemented via adjacency list
	unordered_map< int, vector<edge> > nodes;
	
	public:
			// default constructor creates empty graph
		graph(int S = 0): size(S), nodes ( unordered_map< int, vector<edge> >{} )
		{
			for(int n = 0; n < S; n++)
				nodes[n] = vector<edge>();
		}
		
			// adds a node to the graph, returns true if successful
		bool addNode(int n); 
		
			// deletes node <n> from graph, returns true if successful
		bool delNode(int n);
		
			// total node count
		int getNodeCount() { return size; }
		
			// total edge count
		int getEdgeCount();
		
			// returns true if node "n" exists
		bool nodeExist(int n) { return nodes.count(n) == 1 ? true: false; }
		
			// returns true if there's an edge from node x to y
		bool isAdjacent(int x, int y);
		
			// get all vertices connected to n
		vector<int> getNeighbors(int n);
		
			// adds edge between x & y, if one is currently nonexistent
			// returns true if edge was added, if not return false
		bool addEdge(int x, int y, int d);
		
			// if there's an edge between x & y, delete it and return true
			// else return false
		bool deleteEdge(int x, int y);
		
			// get edge weight/distance from x to y,
			// if there is no edge return -1
		int getEdgeValue(int x, int y);
		
		bool setEdgeValue(int x, int y, int ev);
		
			// get the average path length of all the nodes connected to
			// node "n"
		double avePathLength(int n);
		
		vector<int> getNodes();
};
