#pragma once


#include<functional>
#include<algorithm>
#include<vector>
#include<unordered_set>

using namespace std;


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
		
		bool operator==(nodePath np) {
			return this->eNode == np.eNode;
		}
		
		friend bool operator<(nodePath np1, nodePath np2) { return np1.ect < np2.ect; }
		friend bool operator>(nodePath np1, nodePath np2) { return np1.ect > np2.ect; }
};

template<>
struct hash<nodePath>
{
	size_t operator() (nodePath const& np) const noexcept
	{
		hash<int> eNodeHash;
		return eNodeHash(np.eNode ^ np.ect);
	}
};

struct npHash
{
	size_t operator() (nodePath const& np) const noexcept
	{
    	hash<int> eNodeHash;
    	return eNodeHash(np.eNode ^ np.ect);
	}
};

class MaxPQ
{
	vector<nodePath> npq;

	public:
		MaxPQ( vector<nodePath> N = vector<nodePath>() ): npq(N) {}

		bool empty() { 
			return npq.empty();
		}
		
		bool contains(nodePath node) {
			unordered_set<nodePath> npSet( pqVector.begin(), pqVector.end() );
			return npSet.count(node) == 1;
		}
		
		nodePath getNodePath(nodePath&& np)
		{
			unordered_set<nodePath> npSet( npq.begin(), npq.end() );
			
			if(npSet.count(np) != 1)
				return np;
			else
				return *npSet.find(np);
		}
		
		nodePath add(const nodePath& np)
		{
			npq.push_back(np);
			push_heap( npq.begin(), npq.end() );
			
			return np
		}

		nodePath remove(const nodePath& np)
		{
			unordered_set<nodePath> npSet( npq.begin(), npq.end() );
			npSet.erase(np);
			
			npq = vector<nodePath>( npSet.begin(), npSet.end() );
			make_heap( pqVector.begin(), pqVector.end() );
			
			return np;
		}
		
		void clear() {
			npq.clear();
		}
		
		nodePath top() {
			return npq.front();
		}
		
		nodePath getMax()
		{ 
			pop_heap( npq.begin(), npq.end() );
			nodePath np = npq.back();
			npq.pop_back();

			return np;
		} 
		
		int size() { return npq.size(); }
};

