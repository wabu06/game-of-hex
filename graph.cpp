#include "graph.h"



	// add a vertex/node to graph
bool graph::addNode(int n) 
{ 
	if( nodeExist(n) )
		return false;
	else
	{
		nodes[n] = vector<edge>(); size++; 
		return true;
	}
}

	// deletes a vertex/node from graph
bool graph::delNode(int n)
{
	vector<edge>::iterator V;
	
	if( nodeExist(n) )
	{
		for(auto& E: nodes[n]) // first get neighbors of node <n>
		{
				// then remove <n> from each of it's neighbors
			for(auto itr = nodes[E.node].begin(); itr->node != n; ++itr)
				V = itr;
			
			nodes[E.node].erase(V);
		}
		
		nodes.erase(n);
		
		size--;
		
		return true;
	}
	else
		return false;
}

	// total edge count
int graph::getEdgeCount()
{
	int count = 0;
	
	for(int i = 0; i < size; i++)
	{
		for(auto& E: nodes[i])
		{
			if(E.node > i)
				count++;
		}
	}
	
	return count;
}

	// returns true if there's an edge from node x to y
bool graph::isAdjacent(int x, int y)
{	
	if ( nodeExist(x) && nodeExist(y) )
	{
		for(auto& E: nodes[x])
		{
			if (E.node == y)
				return true;
		}
		
		return false;
	}
	else
		return false;
}

	// get all nodes connected to n
vector<int> graph::getNeighbors(int n)
{
	vector<int> neighbors = vector<int>();
	
	if ( nodeExist(n) )
	{
		for(auto& E: nodes[n])
			neighbors.push_back(E.node);
	}
	
	return neighbors;
}

	// adds edge between x & y, if one is currently nonexistent
	// returns true if edge was added, if not return false
bool graph::addEdge(int x, int y, int d)
{
	if ( nodeExist(x) && nodeExist(y) )
	{
		if ( isAdjacent(x, y) && isAdjacent(y, x) )
			return false;
		else
		{
			nodes[x].push_back( edge(y, d) );
			nodes[y].push_back( edge(x, d) );
		
			return true;
		}
	}
	else
		return false;
}

	// if there's an edge between x & y, delete it and return true
	// else return false
bool graph::deleteEdge(int x, int y)
{	
	if ( nodeExist(x) && nodeExist(y) )
	{
		if ( isAdjacent(x, y) && isAdjacent(y, x) )
		{
			for (auto itr = nodes[x].begin(); itr != nodes[x].end(); ++itr)
			{
				if (itr->node == y)
				{
					nodes[x].erase(itr);
					break;
				}
			}
		
			for (auto itr = nodes[y].begin(); itr != nodes[y].end(); ++itr)
			{
				if (itr->node == x)
				{
					nodes[y].erase(itr);
					break;
				}
			}
		
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

	// get edge weight/distance from x to y, if there is no edge return -1
int graph::getEdgeValue(int x, int y)
{	
	if ( nodeExist(x) && nodeExist(y) )
	{
		for(auto& E: nodes[x])
		{
			if (E.node == y)
				return E.weight;
		}
		
		return -1;
	}
	else
		return -1;
}

bool graph::setEdgeValue(int x, int y, int ev)
{
	if ( nodeExist(x) && nodeExist(y) )
	{
		if ( isAdjacent(x, y) && isAdjacent(y, x) )
		{
			for(auto& E: nodes[x])
			{
				if (E.node == y)
				{
					E.weight = ev;
					break;
				}
			}
			
			for(auto& E: nodes[y])
			{
				if (E.node == x)
				{
					E.weight = ev;
					break;
				}
			}
			
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

	// get the average path length of all the nodes connected to node "n"
double graph::avePathLength(int n)
{
	double total = 0.0;
	
	int eCount;
	
	if ( nodeExist(n) )
	{
		eCount = nodes[n].size();
		
		for(auto& E: nodes[n])
			total += static_cast<double>(E.weight);

		return total / static_cast<double>(eCount);
	}
	else
		return 0.0;
}
