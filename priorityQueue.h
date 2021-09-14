#ifndef DSPATH
#define DSPATH

#include<iostream>
#include<vector>
#include<tuple>

using namespace std;

#endif


	// the "nodePath" class used to represent a list of nodes, corresponding
	// to a particular path and the total edge cost of that path
class nodePath
{
	public:
	int ect; // edge count total of a given node path
	vector<int> nodeList;

	nodePath(int T = 0, vector<int> NL = vector<int>()):
				ect(T), nodeList(NL) {}
};

class priorityQueue
{
	vector<nodePath> pqArray;
	int size;
	
		// make subtree with root at given index priority queue compliant
	void heapify(int);
	
		// get parent node index of node at index i
	int parent(int i) { return (i-1)/2; }
	
		// get index of left child of node at index i
    int left(int i) { return (2*i + 1); }
  
    	// get index of right child of node at index i
    int right(int i) { return (2*i + 2); }
	
	public:
		priorityQueue(int S = 0) { size = S; pqArray = vector<nodePath>(size); }
	
			// removes the top element of the queue
		nodePath getMin(); 

			// checks to see if the priority queue contains node <n> 
			// if so return the index, if not return -1
		int contains(int EC);
		
			// insert node path "np" into queue
		void insert(nodePath np);
		
			// Decreases value of key at index 'i' to new_val
		void decreaseKey(int i, int new_val);
		
			// returns the top element of the queue.
		nodePath top() { return pqArray[0]; }
		
			// returns the number of queue elements
		int getSize() { return size; } 
		
		vector<nodePath> getQueContents();
		
		bool isEmpty() { return size == 0 ? true: false; }
		
		bool notEmpty() { return size > 0 ? true: false; }
		
			// emtpy out the Priority Queue
		void emptyPQ()
		{
			pqArray.clear();
			size = 0;
		}
		
			// modify the element at index i of PQ array
		void modVal(int i, nodePath n) { pqArray[i] = n; }
		
		nodePath getNodePath(int i) { return pqArray[i]; }
};
