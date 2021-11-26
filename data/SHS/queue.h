#include<assert.h>
#include<iostream> 

static const int MAX_NODES = 10000000;

static int queueArray[MAX_NODES];

static int q_size = 0;
static int q_first = 0; // point to the first and last elements, resp

inline int queue_size()
{ 
	return q_size; 
}

inline int queue_pop()
{
	//if (0 == q_size) abort();
	int element = queueArray[q_first];
	++q_first;
	--q_size;
	if (0 == q_size) q_first = 0;
	return element;
}

inline void queue_push(int element)
{
	//assert(q_first + q_size < MAX_NODES);

	queueArray[q_first + q_size] = element;

	++q_size;
}

void queue_clear()
{
	q_size = 0;
	q_first = 0;
}



/*void Queue::freeSpace()
{
	if (NULL != storeArray) delete[]storeArray;
	storeArray = NULL;
	maxSize = size = 0;
	first = last = -1;
}*/

/*int Queue::front()
{
if (size == 0) abort();
return storeArray[first];
}*/



/*void Queue::reserve(int s)
{
assert(s > 0 && storeArray == NULL);
storeArray = new int[s];
maxSize = s;
size = 0;
first = last = -1;
}*/
