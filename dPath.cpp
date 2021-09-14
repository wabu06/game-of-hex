#include "shortestPath.h"



bool dsPath::nodeInClosedSet(int n)
{
	for(auto& N: closedSet)
	{
		if (N.nodeList.back() == n)
			return true;
	}
	
	return false;
}

nodePath dsPath::getNodePath( int sN, int dN)
{
		// what to return if either source or destination nodes are not in the
		// graph
	if( !( spGraph.nodeExist(sN) && spGraph.nodeExist(dN) ) )
		return nodePath( -1, vector<int>() );
	
		// what to return if source and destination nodes are equal
	if (sN == dN)
		return nodePath(0, vector<int>{dN});
	
		// initialize open and closed sets, to empty
	openSet.emptyPQ();
	closedSet.clear();
	
		// place source node in open set
	openSet.insert( nodePath(0, vector<int>{sN}) );
	
	nodePath np;
	
	int cn, ev, tempEV, idx;
	
	vector<int> tempNP;
	
	nodePath LP; // last path added to closed set
	
	vector<int> nodeNeighbors;
	
	while( openSet.notEmpty() )
	{
		np = openSet.getMin(); closedSet.push_back(np);
		
		LP = closedSet.back(); // get most recent path added to closed set
		
			// if final node in the most recent path added to closed set is 
			// "dN", the destination node, then shortest path has been found
		if ( LP.nodeList.back() == dN )
			return LP;

		cn = np.nodeList.back(); // current node to be examined
		
		nodeNeighbors = spGraph.getNeighbors(cn);
		
			// if a node has no neighbors then there isn't a path to the 
			// destination node "dN"
		if (nodeNeighbors.size() == 0)
			return nodePath( -2, vector<int>() );

		for(auto& N: nodeNeighbors)
		{
			if( !cMap[ spGraph.getEdgeColor(cn, N) ] )
				continue;
			
			if( nodeInClosedSet(N) )
				continue;
			
			tempEV = np.ect;
			tempNP = np.nodeList;
			
				// returns the index of the node in the open set, if node is not
				// in the open set return -1
			idx = openSet.contains(N);
		
			ev = spGraph.getEdgeValue(cn, N);
			
			tempEV += ev;
			
			tempNP.push_back(N);
			
				// add new path to open set if the node is leads to isn't
				// already ready visited, if it's already been visited, add it
				// only if it's better path than one already checked/found
			if (idx < 0)
				openSet.insert( nodePath(tempEV, tempNP) );
			else
			{
				if ( tempEV < openSet.getNodePath(idx).ect )
				{
					openSet.decreaseKey(idx, tempEV);
					
						// need to find new index, after decreasing the PQ key
						// the keys in question are the edge count totals
					idx = openSet.contains(N);
					
					openSet.modVal( idx, nodePath(tempEV, tempNP) );
				}
			}
		}
		
		//np = openSet.getMin(); // get shortest path currently in open set
		
		//closedSet.push_back(np);
	}
	
		// return empty path list if node "dN" is not reachable from node "sN"
	return nodePath( -3, vector<int>() );
}
