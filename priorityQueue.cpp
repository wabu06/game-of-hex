#include "priorityQueue.h"

void PQswap(nodePath& x, nodePath& y)
{
    nodePath temp = x;
    x = y;
    y = temp;
}

	// make subtree with root at given index priority queue compliant
void priorityQueue::heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	
	if (l < size && pqArray[l].ect < pqArray[i].ect)
    	smallest = l;

	if (r < size && pqArray[r].ect < pqArray[smallest].ect)
    	smallest = r;

	if (smallest != i)
	{
    	PQswap(pqArray[i], pqArray[smallest]);
    	heapify(smallest);
	}
}

	// removes the top element of the queue
nodePath priorityQueue::getMin()
{
	if (size <= 0)
    	return nodePath(-1);

	nodePath root;

	if (size == 1)
	{
    	size--;
		
		root = pqArray[0];
		pqArray.pop_back();
		
    	return root;
	}
	
	root = pqArray[0];
	
	pqArray[0] = pqArray[size-1];
	
	size--;
	
	heapify(0);
	
	pqArray.pop_back();
	
	return root;
}

	// checks to see if the priority queue contains node <n> 
	// if so return the index, if not return -1
int priorityQueue::contains(int n)
{
	for(int i = 0; i < size; i++)
	{
		if (pqArray[i].nodeList.back() == n)
			return i;
	}
	
	return -1;
}

	// insert node path "np" into queue
void priorityQueue::insert(nodePath np)
{
	size++;
	int i = size - 1;
	
	pqArray.push_back(np);
	
		// make priority queue compliant
    while (i != 0 && pqArray[parent(i)].ect > pqArray[i].ect)
    {
       PQswap(pqArray[i], pqArray[parent(i)]);
       i = parent(i);
    }
}

	// Decreases value of key at index 'i' to new_val
void priorityQueue::decreaseKey(int i, int new_val)
{
	pqArray[i].ect = new_val;
	
		// make priority queue compliant
	while (i != 0 && pqArray[parent(i)].ect > pqArray[i].ect)
	{
		PQswap(pqArray[i], pqArray[parent(i)]);
		i = parent(i);
	}
}

vector<nodePath> priorityQueue::getQueContents()
{
	vector<nodePath> elements;
	
	for(auto& E: pqArray)
		elements.push_back(E);
	
	return elements;
}
