#include<stdio.h>
#include<assert.h>
#include<vector>
using namespace std;

const int MAX_ROWS = 100000000;

// this class defines a data structure, called non-uniform array,
// which is a two-dimensional array, but the sizes of different rows
// may vary significantly.
// The reason for defining this data structure is that it is very time-comsuming
// to do the two operations of `new' and 'delete', since a 'new' and and a 'delete'
// operaton are need for the adjacent list of each vertex. 
// Therefore, there are O(n) such operations.
// The interal data structure of the non-uniform array in fact is a one-dementional array.
// Only O(1) 'new' and 'delete' operations are needed.
// Three basic methods: 
// (1) void allocateMemory(const vector<int> &sizesOfRows)
//      the vector tells the size of row, which are the maximum numbers of 
//        possible elements that can be stored at each row 
// (2) void push_back(int i, int element)
//     store the element at the end of row i
// (3) int & access(int i, int j)
//      access the (j+1) th element at row (i+1)
class nonUniformArray{
public:
	void allocateMemory(const vector<int> &sizesOfRows);
	inline int size(); // how many rows
	inline int size(int i); // how many elements in row i
	// store the element at the end of row i
	inline void push_back(int i, int element);
	inline int & access(int i, int j); // access the element at row i and column j
	void erase(int i, int element);  // erase the element from row i
	bool find(int i, int element); // whether the element is contained in row i
	void printArray();
	void clear(); // clear all  elements
	void clear(int i); // clear row i
	void reserve(int s);
public:
	nonUniformArray();
	~nonUniformArray();
	nonUniformArray(const nonUniformArray & other);
	nonUniformArray & operator=(const nonUniformArray & other);
protected:
	int *storeArray; // store the two dimensional array into one sequential array
	int arraySize;
	int* maxSize = new int[MAX_ROWS]; // the max size of each row
	int* sizeEachRow= new int[MAX_ROWS]; // how many elements stored at each row
	int* baseEachRow= new int[MAX_ROWS]; // the base of each row
	int numRows; // total number of rows
};

void nonUniformArray::reserve(int s)
{
	assert(s >= 0);
	if (s <= arraySize) return;

	int *newArray = new int[s];
	for (int i = 0; i < arraySize; ++i) // copy
		newArray[i] = storeArray[i]; 
	if (NULL != storeArray) delete[]storeArray;
	storeArray = newArray;
	arraySize = s;
}

void nonUniformArray::clear(int i) // clear row i
{
	assert(i >= 0 && i < numRows);
	sizeEachRow[i] = 0;
}

bool nonUniformArray::find(int i, int element)
{
	assert(i >= 0 && i < numRows);
	for (int j = 0; j < sizeEachRow[i]; ++j)
		if (storeArray[baseEachRow[i] + j] == element) return true;
	return false;
}

void nonUniformArray::erase(int i, int element)
{  // erase the element from row i
	assert(i >= 0 && i < numRows);
	int j;
	for (j = 0; j < sizeEachRow[i]; ++j)
		if (storeArray[ baseEachRow[i] + j ] == element) break;
	assert(j != sizeEachRow[i]); // the element must be found
	for (j; j <= sizeEachRow[i] - 2; ++j)
		storeArray[baseEachRow[i] + j] = storeArray[baseEachRow[i] + (j + 1)];
	--sizeEachRow[i];
}

inline int & nonUniformArray::access(int i, int j)
{ // access the element at row i and column j
	//assert(i >= 0 && i < numRows);
	//assert(j >= 0 && j < sizeEachRow[i]);
	return storeArray[ baseEachRow[i] + j];
}

inline void nonUniformArray::push_back(int i, int element)
{ // store the element at the end of row i
	//assert(i >= 0 && i < numRows);
	//assert(sizeEachRow[i] < maxSize[i]); // there are some storage left
	storeArray[ baseEachRow[i] + sizeEachRow[i] ] = element; // store the element
	++sizeEachRow[i];
}


inline int nonUniformArray::size(int i)
{ // how many elements in row i
	assert(i >= 0 && i < numRows);
	return sizeEachRow[i];
}

inline int nonUniformArray::size() // how many rows
{
	return numRows;
}

void nonUniformArray::allocateMemory(const vector<int> &sizesOfRows)
{
	assert(sizesOfRows.size() > 0 &&
		sizesOfRows.size() <= MAX_ROWS);
	
	int i;
	int numElements = 0;
	for (i = 0; i < sizesOfRows.size(); ++i)
	{
		assert(sizesOfRows[i] >= 0);
		maxSize[i] = sizesOfRows[i];
		numElements += maxSize[i]; // count how many elements are needed
		sizeEachRow[i] = 0;
	}

	assert(numElements <= 500000000);
	
	if (numElements > arraySize)
	{
		// clear allocated memory
		if ( NULL != storeArray) delete[] storeArray; 
		storeArray = new int[numElements];
		arraySize = numElements;
	} // else 
	numRows = sizesOfRows.size();
	
	int base = 0;
	for (i = 0; i < numRows; ++i)
	{
		baseEachRow[i] = base;
		base += maxSize[i];
	}
}

nonUniformArray & nonUniformArray::operator = (const nonUniformArray & other)
{
	if (this == &other) return *this;

	// clear allocated memory
	if (NULL != storeArray) delete[]storeArray;

	if (other.arraySize == 0)
	{
		numRows = 0;
		storeArray = NULL;
		arraySize = 0;
		return *this;
	}

	numRows = other.numRows;
	arraySize = other.arraySize;
	int i;
	for (i = 0; i < numRows; ++i)
	{
		maxSize[i] = other.maxSize[i];
		sizeEachRow[i] = other.sizeEachRow[i];
		baseEachRow[i] = other.baseEachRow[i];
	}
	storeArray = new int[arraySize];
	for (i = 0; i < arraySize; ++i)
		storeArray[i] = other.storeArray[i];

	return *this;
}

nonUniformArray::nonUniformArray(const nonUniformArray & other)
{
	if (other.arraySize == 0)
	{
		numRows = 0;
		arraySize = 0;
		storeArray = NULL;
		return;
	}

	numRows = other.numRows;
	arraySize = other.arraySize;
	int i;
	for (i = 0; i < numRows; ++i)
	{
		maxSize[i] = other.maxSize[i];
		sizeEachRow[i] = other.sizeEachRow[i];
		baseEachRow[i] = other.baseEachRow[i];
	}
	
	storeArray = new int[arraySize];
	for (i = 0; i < arraySize; ++i)
		storeArray[i] = other.storeArray[i];
}

void nonUniformArray::printArray()
{
	assert(numRows > 0);
	int i, j;
	for (i = 0; i < numRows; ++i)
	{
		printf("row %d:\t", i);
		for (j = 0; j < sizeEachRow[i]; ++j)
			printf("%d ", storeArray[ baseEachRow[i]+j ] );
		printf("\n");
	}
}

nonUniformArray::nonUniformArray()
{
	storeArray = NULL;
	arraySize = 0;
	numRows = 0;
}

nonUniformArray::~nonUniformArray()
{
	if (NULL != storeArray) delete[] storeArray;
}

void nonUniformArray::clear()
{
	numRows = 0;
}

