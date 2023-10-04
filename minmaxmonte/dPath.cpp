#include "dPath.h"


nodePath dsPath::getNodePath( int sN, int dN)
{
		// what to return if either source or destination nodes are not in the graph
	if( !( spGraph.nodeExist(sN) && spGraph.nodeExist(dN) ) )
		return nodePath(-1, -1, vector<int>() );
	
		// what to return if source and destination nodes are equal
	if (sN == dN)
		return nodePath(dN, 0, vector<int>{sN, dN});
	
		// initialize open and closed sets, to empty
	openSet.clear();
	closedSet.clear();
	
		// place source node in open set
	openSet.add( nodePath(sN, 0, vector<int>{sN}) );
		
	while( !openSet.empty() )
	{
		nodePath np; np = openSet.getTop(); closedSet[np.eNode] = np;
			
			// if destination node "dN" is in the closed set then longest path has been found
		if ( closedSet.count(dN) == 1)
			return closedSet[dN];

		int cn = np.eNode; // current node to be examined
		
		vector<int> nodeNeighbors = spGraph.getNeighbors(cn);
		
			// if a node has no neighbors then there isn't a path to the destination node "dN"
		if (nodeNeighbors.size() == 0)
			return nodePath(-2, -2, vector<int>() );

		for(auto& N: nodeNeighbors)
		{	
				// do not add a path to the open set if it's in the closed set
			if( closedSet.count(N) == 1)
				continue;
			
			int tempEV = np.ect;
			vector<int> tempNP = np.nodeList;
		
			int ev = spGraph.getEdgeValue(cn, N);
			
			tempEV += ev;
			
			tempNP.push_back(N);
			
				// if current node is in openSet only add it, if it's edge value is greater
			if( openSet.contains( nodePath(N, tempEV, tempNP) ) ) 
			{
				nodePath npOS = openSet.getNodePath( nodePath(N, tempEV, tempNP) );
	
				if(tempEV > npOS.ect)
				{
					openSet.remove(npOS);
					openSet.add( nodePath(N, tempEV, tempNP) );
				}
			}
			else
				openSet.add( nodePath(N, tempEV, tempNP) );
		}		
	}
		// return empty path list if node "dN" is not reachable from node "sN"
	return nodePath(-3, -3, vector<int>() );
}
