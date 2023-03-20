#pragma once

#include<unordered_map>

using namespace std;

class edge
{
    public:
        int node;
        int weight;

        edge(int N = -1, int W = 0): node(N), weight(W) {}
};

class graph
{
    unordered_map< int, unordered_map< int, edge> > nodes;
    int size;

    public:
        graph(int S = 0): size(S), nodes( unordered_map< int, unordered_map<int, edge> > {} )
        {
            for(int n = 0; n < S; n++)
                nodes[n] = unordered_map<int, edge> {};
        }
        
        graph(const graph& srcGraph): nodes(srcGraph.nodes), size(srcGraph.size) {}

        int getSize() { return size; }
        bool nodeExist(int n) { return nodes.count(n) == 1; }

		int getNodeCount() { return nodes.size(); }

        bool isAdjacent(int n1, int n2)
        {
            if( nodeExist(n1) && nodeExist(n2) )
                return ( nodes[n1].count(n2) ) == 1 && ( nodes[n2].count(n1) == 1 );
            else
                return false;
        }

        bool addNode(int n)
        {
            if( nodeExist(n) )
                return false;
            else
            {
                nodes[n] = unordered_map<int, edge> {};
                return true;
            }
        }

        bool addEdge(int n1, int n2, int w)
        {
            if( isAdjacent(n1, n2) && isAdjacent(n2, n1) )
                return false;
            else
            {
                nodes[n1][n2] = edge(n2, w);
                nodes[n2][n1] = edge(n1, w);

                return true;
            }
        }

        vector<int> getNeighbors(int n)
        {
            vector<int> neighbors = vector<int>();

            for(const auto& N: nodes[n] )
                neighbors.push_back(N.first);

            return neighbors; 
        }

        int getEdgeValue(int n1, int n2)
        { 
            if( isAdjacent(n1, n2) )
                return nodes[n1][n2].weight;
            else
                return -1;
        }
};

