#include<iostream>
#include<fstream>
#include<stdio.h>
#include<assert.h>
#include<vector>
#include<time.h>
#include <algorithm>
#include "queue.h"
#include "nonUniformArray.h"
using namespace std;

static clock_t timeAlg = 0;


static double zeta; // the large shortest distance of two unreachable nodes

// static const int MAX_NODES = 5400000;

// for DFS
static bool visited[MAX_NODES]; // whether it has been visited before

// for shortest distance computation
static int distances[MAX_NODES]; // distances to a source node
static double sumDistance[MAX_NODES]; // W(v) for each node
static int parentSPT[MAX_NODES]; // the parent in the shortest path tree 

// the randmized algorithm for all-pairs shortest distance estimation
//vector<int> sampleSet; //  
//static double sampleProb[MAX_NODES];
//static double sampleCoefficients[MAX_NODES];
//static bool tested[MAX_NODES];

//static Queue  bfsQueue; // 

class Hole;

struct Node
{
	int id;
	double key;
	Node(int a, double b){ id = a; key = b; }
	Node(){}
	bool operator>(Node &e)
	{
		if (key > e.key) return true;
		else					return false;
	}
	bool operator>=(Node &e)
	{
		if (key > e.key) return true;
		else					return false;
	}
	bool operator<(Node &e)
	{
		if (key < e.key) return true;
		else					return false;
	}
	bool operator<=(Node &e)
	{
		if (key < e.key) return true;
		else					return false;
	}
};





inline bool comp(const Node & a, const Node & b) // operator >
{
	return a.key > b.key;
}

static int Mode = 9973;
double Uniform()
{
	return (rand() % Mode) / (double)Mode;
}

inline void swap(int &u, int &v)
{
	int tmp = u;
	u = v;
	v = tmp;
}

struct Edge{
	int u, v;
	Edge(int a, int b){ u = a; v = b; }
	Edge(){}
};

class Graph{
public:
	friend class Hole;
	friend class HAM;
public:
	void readGraph(const char *graphFile);
	void printGraph();
	int findAllCCsDFS(nonUniformArray &allCCs); // find all connected components
	int findAllCCsBFS(nonUniformArray &allCCs); // find all connected components
	void findAPsAndLowerBounds();
	int maxDegree();
	void cleanGraph(const char *graphFile);
	Graph();
	Graph(const Graph &g);
	Graph & operator=(const Graph &g);
	~Graph();

public:
	void readCommunities(char *communitiesFileName);
	void evaluateHolesByCommSpan(const vector<int> &foundHoles, int *numComSpan, int *sumComSizeSpan);
// for shortest distance
public:
	int numOfEdges();
	int numOfNodes(){ return n; }
protected:
	double sumOfAllPairsShortestDistances();
	void rankByClosenessCentralities(vector<int> &rankedNodes);
	double exactAllSum();

protected:
	void rankByPathCount(vector<int> &rankedNodes);
protected:
	void rankBy2Step(vector<int> &rankedNodes);
protected:
	void rankbyPageRank(vector<int> &rankedNodes);
protected:
	int findWellPositionedNode();
	double estimateAllSum(vector<int> & sampleSet, double *sampleProb);
	void computeSampleCoefficients(int wpNode, double *sampleCoefficients);
	void findSampleSet(int wpNode, vector<int> & sampleSet, double *sampleProb);
	// single-source shortest distance
	void shortestDistances(int src, int & medianNode, double & medianDis);
	void shortestDistances(int src, bool markSPT);
protected:
	void modifiedDFS(int u, nonUniformArray & allCCs, int numNodesValid);
	inline void DFS(int u, int CCID, int & sizeOfCC);
	void clearGraph();
protected:
	nonUniformArray adjLists;
	int n, m; // number of nodes and edges in the graph
	// whether a node is valid in the graph, as it may be identified as a structural hole
	// and removed
	bool *isValid;

public: //for DFS
	void initilizeVariables();
	void clearVariables();
	void allocateVariablesForDFS();
private: // for DFS
	int *numChildren; // number of chidren in the DFS tree
	int *numNodesSubtree; // number of nodes in the subtree rooted at each node in the DFS tree
	int *parent; // the parent of each node in the DFS tree
	bool *isAP; // whether the node is an Articulation point
	int *discoveredTime; // the discovered time of each vertex
	int *lowestTime; // the smallest discovered time of any neighbor of u’s descendants (through a back-edge)
	double *lowerBounds; // the lower bound for each node
	int time; // global time counter

protected:
	vector<int> sizeofEachCC; // the number of nodes in each connected component
	int *ccBelongto; // the cc id that each node belongs to

protected:
	vector<int> communities;
	nonUniformArray allCommunities;
private:
	bool debug; //
};

int Graph::numOfEdges()
{
	int edges = 0;
	for (int i = 0; i < adjLists.size(); ++i)
		edges += adjLists.size(i);
	return edges / 2;
}

void Graph::evaluateHolesByCommSpan(const vector<int> &foundHoles, int *numComSpan, int *sumComSizeSpan)
{
	int numCom = 0;
	int sumComSize = 0;
	int i, j;
	int hole;

	bool *isSpanned = new bool[allCommunities.size()];
	for (i = 0; i < allCommunities.size(); ++i) isSpanned[i] = false;
	
	int comID;
	for (i = 0; i < foundHoles.size(); ++i)
	{
		hole = foundHoles[i];
		comID = communities[hole];
		if (-1 != comID && false == isSpanned[comID])
		{
			isSpanned[comID] = true;
			++numCom;
			sumComSize += allCommunities.size(comID);
		}
		for (j = 0; j < adjLists.size(hole); ++j)
		{
			comID = communities[ adjLists.access(hole, j) ];
			if (-1 == comID) continue;
			if (true == isSpanned[comID]) continue;
			
			isSpanned[comID] = true;
			++numCom;
			sumComSize += allCommunities.size(comID);
		}
		numComSpan[i] = numCom;
		sumComSizeSpan[i] = sumComSize;
		//printf("%d, numComSpan: %d, sumComSizeSpan: %d\n", i + 1, numComSpan[i], sumComSizeSpan[i]);
	}
	//printf("allCommunities: %d\n", allCommunities.size());


	delete[]isSpanned;
}

void Graph::readCommunities(char *communitiesFileName)
{
	ifstream in(communitiesFileName);
	if (!in) abort();
	communities.clear();
	communities.reserve(n);
	int curCom;
	int i;
	for (i = 0; i < n; ++i)
	{
		in >> curCom;
		communities.push_back( curCom );
	}

	int maxComID = -1;  // the max community ID
	for (i = 0; i < n; ++i) 
		if (communities[i] > maxComID) maxComID = communities[i];
	vector<int> sizeOfEachCom;
	sizeOfEachCom.resize(maxComID + 1, 0);
	for (i = 0; i < n; ++i)
		++sizeOfEachCom[ communities[i] ];

	allCommunities.clear();
	allCommunities.allocateMemory(sizeOfEachCom);
	for (i = 0; i < n; ++i)
		allCommunities.push_back(communities[i], i);

	in.close();
}

int Graph::maxDegree()
{
	int md = 0;
	for (int i = 0; i < n; ++i)
		if (adjLists.size(i) > md) md = adjLists.size(i);

	int sum = 0;
	for (int i = 0; i < n; ++i) sum += adjLists.size(i);
	printf("m:%d , sumDegree/2: %d\n", m, sum / 2);

	return md;
}

double Graph::sumOfAllPairsShortestDistances()
{ //Pre: the graph is connected and the weight of each node is one
  // Return: the estimated sum
  // Reference: see paper "Average Distance Queries throughWeighted Samples in Graphs and
  // Metric Spaces: High Scalability with Tight Statistical Guarantees"

	if (n <= 50) return exactAllSum();

	int wpNode = findWellPositionedNode();
	vector<int> sampleSet;
	double *sampleProb = new double[n];
	findSampleSet(wpNode, sampleSet, sampleProb );

	//if (sampleSet.size() > 100) printf("sample set: %d\n", sampleSet.size());

	double sum = estimateAllSum(sampleSet, sampleProb);
	if (debug) printf("sumOfAllPairsShortestDistances: %.2lf\n", sum);

	delete[]sampleProb;
	return sum;
}

void Graph::rankByClosenessCentralities(vector<int> &rankedNodes)
{  //Pre: the graph is connected and the weight of each node is one
  // Return: nodes in the network are ranked by their closeness centralities
  // Reference: see paper "Average Distance Queries throughWeighted Samples in Graphs and
  // Metric Spaces: High Scalability with Tight Statistical Guarantees"

	int wpNode = findWellPositionedNode();
	vector<int> sampleSet;
	double *sampleProb = new double[n];
	findSampleSet(wpNode, sampleSet, sampleProb);

	//if (sampleSet.size() > 100) printf("sample set: %d\n", sampleSet.size());

	 estimateAllSum(sampleSet, sampleProb);

	 vector<Node> allNodes;
	 allNodes.reserve(n);
	 for (int i = 0; i < n; ++i)
	 {
		 if (false == isValid[i]) continue;
		 sumDistance[i] /= n; // average 
		 allNodes.push_back(Node(i, 1.0/sumDistance[i])); // centralities
	 }
	 sort(allNodes.begin(), allNodes.end(), comp); // decreasing order

	 rankedNodes.clear();
	 rankedNodes.reserve( allNodes.size() );
	 for (int i = 0; i < allNodes.size(); ++i)
	 {
		 rankedNodes.push_back(allNodes[i].id);
		// if (i < 50) printf("%d, node %d, avg dis: %.6lf\n", i, allNodes[i].id, 1.0/ allNodes[i].key);
	 }	 

	delete[]sampleProb;
}

void Graph::rankBy2Step(vector<int> &rankedNodes)
{ //Pre: the graph is connected and the weight of each node is one
// Return: nodes in the network are ranked by their path count score
// usage: we count the number of 2-hops shortest paths that each vertex lies in
//        and rank the vertices in decreasing order
// For each vertex vi, let N(vi) be the set of neighbors of the vertex. let ki=|N(vi|
// the number of 2-hop paths that contains vertex vi is ki(ki-1) - 2*m_{G[N(vi)]},
// where m_{G[N(vi}]} is the number of the induced graph G[N(vi)] by the neighbor set

	int i, j, t;
	int *count = new int[n];
	for (i = 0; i < n; ++i) count[i] = 0;

	bool *isNeighbor = new bool[n];
	for (i = 0; i < n; ++i) isNeighbor[i] = false;

	int ki;
	int u, v;
	for (i = 0; i < n; ++i)
	{
		ki = adjLists.size(i);
		if ( ki <= 1) continue; // no more than one neighbor

		for (j = 0; j < ki; ++j)
			isNeighbor[ adjLists.access(i, j) ] = true;

		for (j = 0; j < ki; ++j)
		{
			u = adjLists.access(i, j); // each neighbor
			for (t = 0; t < adjLists.size(u); ++t) // access the adjlist of each list
			{
				v = adjLists.access(u, t);
				//if (v == i) continue; // it is node vi
				if (false == isNeighbor[v]) continue; // not an edge among neighbors
				++count[i]; // count the number of edges among neighbors of node vi
			}
		}
		count[i] = ki *(ki - 1) - count[i];

		for (j = 0; j < ki; ++j)
			isNeighbor[adjLists.access(i, j)] = false;
	}


	vector<Node> allNodes;
	allNodes.reserve(n);
	for (i = 0; i < n; ++i) allNodes.push_back(Node(i, count[i]));
	sort(allNodes.begin(), allNodes.end(), comp); //sort the count in decreasing order
	Node node;
	rankedNodes.clear();
	rankedNodes.reserve(n);
	for (i = 0; i < allNodes.size(); ++i)
	{
		node = allNodes[i];
		rankedNodes.push_back(node.id);
		//if (i < 10) printf("%d, count: %.0lf\n", i, node.key);
	}
	delete[]isNeighbor;
	delete[]count;
}

void Graph::rankbyPageRank(vector<int> &rankedNodes)
{
	//Pre: the graph is connected 
	// Return: nodes in the network are ranked by their page rank score r(v)
	// usage: r(v) = (1-alpha)/n + alpha * \sum_{u in N(v)} r(u)/deg(u),
	// alpha = 0.85

	int j;
	int u, v;
	double *r = new double[n];
	double *newR = new double[n];
	for (v = 0; v < n; ++v) r[v] = 1.0/n;

	int nv;
	double alpha = 0.85;
	int RecursionMax = 20;
	for (int i = 0; i < RecursionMax; ++i)
	{
		for (v = 0; v < n; ++v)
		{
			nv = adjLists.size(v);
			if (nv == 0)
			{
				newR[v] = r[v]; // no neighbor
				continue;
			}

			newR[v] = (1 - alpha) / n;
			for (j = 0; j < nv; ++j)
			{
				u = adjLists.access(v, j); // each neighbor
				newR[v] += alpha * r[u] / adjLists.size(u);
			}
		}
		for (v = 0; v < n; ++v) r[v] = newR[v];
	}
	
	vector<Node> allNodes;
	allNodes.reserve(n);
	for (int i = 0; i < n; ++i) allNodes.push_back(Node(i, r[i]));
	sort(allNodes.begin(), allNodes.end(), comp); //sort the count in decreasing order
	Node node;
	rankedNodes.clear();
	rankedNodes.reserve(n);
	for (int i = 0; i < allNodes.size(); ++i)
	{
		node = allNodes[i];
		rankedNodes.push_back(node.id);
		//if (i < 10) printf("%d, count: %.0lf\n", i, node.key);
	}

	delete[]r;
	delete[]newR;
}

void Graph::rankByPathCount(vector<int> &rankedNodes)
{ //Pre: the graph is connected and the weight of each node is one
	// Return: nodes in the network are ranked by their path count score
	// usage: we count the number of shortest paths that each vertex lies in
	//        and rank the vertices in decreasing order
	
	clock_t st = clock();
	int i, j;
	int *count = new int[n];
	for (i = 0; i < n; ++i) count[i] = 0;

	Graph spt; // shortest path tree
	spt.n = n;
	spt.isValid = new bool[n];
	for (i = 0; i < n; ++i) spt.isValid[i] = true;
	spt.adjLists.reserve(2 * n); // no more than (n-1) edges
	vector<int> degrees; // degrees of each node in the SPT
	int sizeofCC; // this variable is not used
	int src; 

	vector<int> testNodes;
	int maxNumNodes = 2000; // 10 k nodes
	testNodes.reserve(maxNumNodes);
	if (n <= maxNumNodes)
	{
		for (i = 0; i < n; ++i) testNodes.push_back(i); // include all nodes
	}
	else{ // only randomly select 10 k nodes
		bool *found = new bool[n];
		for (i = 0; i < n; ++i) found[i] = false;
		int numFound = 0;
		int index;
		while (numFound < maxNumNodes)
		{
			index = int(Uniform()*n);
			if (index == n) index = n - 1;
			if (true == found[index]) continue;
			found[index] = true;
			testNodes.push_back(index);
			++numFound;
		}
		delete[]found;
	}

	for (i = 0; i < testNodes.size(); ++i)
	{
		//if (i % 1000 == 0 && i > 0) 
			printf("%d th node\n", i);
		src = testNodes[i];
		shortestDistances(src, true); // find the shortest paths from each node 
		if (debug) printf("src: %d: \n", src);

		degrees.clear();
		degrees.resize(n, 0);
		for (j = 0; j < n; ++j) // count the degree of each node in the SPT
		{
			if (-1 == parentSPT[j]) continue;
			++degrees[j];
			++degrees[ parentSPT[j] ];
			if (debug) printf("%d->%d, ", parentSPT[j], j);
		}
		if (debug) printf("\n");

		spt.adjLists.clear();
		spt.adjLists.allocateMemory(degrees);
		for (j = 0; j < n; ++j) // construct the SPT graph
		{
			if (-1 == parentSPT[j]) continue;
			spt.adjLists.push_back(j,  parentSPT[j]);
			spt.adjLists.push_back(parentSPT[j], j);
		}
		//spt.printGraph();
		
		spt.allocateVariablesForDFS();
		sizeofCC = 0;
		spt.DFS(src, 0, sizeofCC);  // count the number of nodes in each subtree

		for (j = 0; j < n; ++j)
		{
			if (-1 == spt.parent[j]) continue; // it should not the parent
			count[j] += spt.numNodesSubtree[j] - 1; // exclude itself
			if (debug)
				printf("node %d, numSubtrees: %d\n", j, spt.numNodesSubtree[j]);
		}
	}

	vector<Node> allNodes;
	allNodes.reserve(n);
	for (i = 0; i < n; ++i)
		allNodes.push_back( Node(i, count[i]) );
	sort(allNodes.begin(), allNodes.end(), comp); //sort the count in decreasing order
	Node node;
	rankedNodes.clear();
	rankedNodes.reserve(n);
	for (i = 0; i < allNodes.size(); ++i)
	{
		node = allNodes[i];
		rankedNodes.push_back(node.id);
		//if (i < 10) printf("%d, count: %.0lf\n", i, node.key);
	}

	delete[]count;

	
}

double Graph::exactAllSum()
{
	if (n <=1 ) return 0;

	allocateVariablesForDFS();

	vector<int> sampleSet;
	sampleSet.reserve(n);
	int i; 
	for (i = 0; i < n; ++i) sampleSet.push_back( i );
	double *sampleProb = new double[n];
	for (i = 0; i < n; ++i) sampleProb[i] = 1.0;

	double sum = estimateAllSum(sampleSet, sampleProb);

	delete []sampleProb;

	return sum;
}

double Graph::estimateAllSum(vector<int> & sampleSet, double *sampleProb)
{
	int i;
	for (i = 0; i < n; ++i) sumDistance[i] = 0;

	int u, v;
	//int a; double b; // virtual variables
	
	for (i = 0; i < sampleSet.size(); ++i)
	{
		u = sampleSet[i]; // a sample node
		//shortestDistances(u, a, b);
		shortestDistances(u, false);
		for (v = 0; v < n; ++v)
			sumDistance[v] += distances[v] / sampleProb[u];
	}
	double sum = 0;
	for (i = 0; i < n; ++i) sum += sumDistance[i];

	return sum;
}

void Graph::findSampleSet(int wpNode, vector<int> & sampleSet, double *sampleProb)
{
	sampleSet.clear();
	double *sampleCoefficients = new double[n];
	computeSampleCoefficients(wpNode, sampleCoefficients);

	double epsilon = 0.1;
	double errorProb = 0.1;
	double k; 
	//k = log(1.0 / errorProb) / (epsilon * epsilon);
	k = 0.5 / (epsilon * epsilon);

	if( debug ) printf("\nsample prob: \n");
	int i;
	for (i = 0; i < n; ++i)
	{
		sampleProb[i] = k * sampleCoefficients[i];
		if (sampleProb[i] > 1.0)  sampleProb[i] = 1.0;
		if (debug) printf("%d, %.4lf\n", i, sampleProb[i]);
	}

	if (debug) printf("\nchosen nodes:\n");
	sampleSet.reserve(400);
	for (i = 0; i < n; ++i)
		if (Uniform() < sampleProb[i])
		{
			sampleSet.push_back(i);
			if (debug) printf("%d ", i);
		}
	if (debug) printf("\n");

	delete[]sampleCoefficients;
}

void Graph::computeSampleCoefficients(int wpNode, double *sampleCoefficients)
{
	int i;
	double smallestCoe = 1.0 / n;
	for (i = 0; i < n; ++i) sampleCoefficients[i] = smallestCoe;

	//int a; double b; // two virtual variables
	// the shortest distances to the well-positioned node
	//shortestDistances(wpNode, a, b);
	shortestDistances(wpNode, false);
	double sumDis = 0;
	for (i = 0; i < n; ++i) sumDis += distances[i]; // the sum
	for (i = 0; i < n; ++i)
		if (distances[i] / sumDis > sampleCoefficients[i])
			sampleCoefficients[i] = distances[i] / sumDis;

	if (debug) printf("\nsample coefficients:\n");
	for (i = 0; i < n; ++i)
		if (debug) printf("%d, %.4lf\n", i, sampleCoefficients[i]);
}

int Graph::findWellPositionedNode()
{
	int maxTestNodes = 10; 
	if (maxTestNodes > n) maxTestNodes = n - 1;
	int i;
	bool *tested = new bool[n];
	for (i = 0; i < n; ++i) tested[i] = false;

	int numTested = 0;
	int curNode;
	int minMedianNode, medianNode;
	double minMedianDis = n, medianDis;
	while (numTested < maxTestNodes)
	{
		curNode = rand() % n; 
		if (true == tested[curNode]) continue;

		tested[ curNode ] = true;
		++numTested;
		shortestDistances(curNode, medianNode, medianDis);
		if (debug) printf("median node: %d, dis: %d\n", medianNode, (int)medianDis);
		if (medianDis < minMedianDis)
		{
			minMedianNode = medianNode;
			minMedianDis = medianDis;
		}
	}
	delete[]tested;
	if (debug) printf("\nminMedianNode: %d, minMedianDis: %d\n", minMedianNode, (int)minMedianDis);

	return minMedianNode;
}

void Graph::shortestDistances(int src, 
	    int & medianNode, double & medianDis)
{
	int i;
	for (i = 0; i < n; ++i) visited[i] = false;
	visited[src] = true;
	queue_clear(); // clear the queue
	queue_push(src);
	distances[src] = 0;

	if (debug) printf("\nsingle-source shortest distance from src: %d\n", src);
	int u, v;
	int j;
	// the number of nodes that their shortest distances to src have been found
	int numDistancesFound = 0; 
	int sz;
	int *adj;
	while (queue_size() > 0 )
	{
		u = queue_pop();

		++numDistancesFound;
		if (debug) printf("node %d, dis: %d\n", u, (int)distances[u]);
		if (numDistancesFound == (n + 2) / 2) // the floor of (n+2)/2
		{
			medianNode = u;
			medianDis = distances[u];
		}

		sz = adjLists.size(u);
		adj = &adjLists.access(u, 0);
		for (j = 0; j < sz; ++j)
		{
			v = adj[ j ];
			if (true == visited[ v ]) continue;
			visited[ v ] = true;
			distances[v] = distances[u] + 1;
			queue_push(v);
		}
	}
	assert(numDistancesFound == n);
}

void Graph::shortestDistances(int src, bool markSPT)
{
	int i, j;
	for (i = 0; i < n; ++i) visited[i] = false;
	if (true == markSPT)
		for (i = 0; i < n; ++i) parentSPT[i] = -1;
	visited[src] = true;
	distances[src] = 0;
	queue_clear(); // clear the queue
	queue_push(src);

	int u, v;
	// the number of nodes that their shortest distances to src have been found
	//int numDistancesFound = 0;
	int sz;
	int *adj; 
	while (queue_size() > 0 )
	{
		u = queue_pop();

		//++numDistancesFound;
		//if (debug) printf("node %d, dis: %d\n", u, (int)distances[u]);

		sz = adjLists.size(u);
		adj = & adjLists.access(u, 0);
		for (j = 0; j < sz; ++j)
		{
			//v = adjLists.access(u, j);
			if ( visited[ adj[j] ] ) continue;
			v = adj[ j ];
			visited[v] = true;
			distances[v] = distances[u] + 1;
			queue_push(v);
			if ( markSPT ) parentSPT[v] = u;
		}
	}
	//assert(numDistancesFound == n);
}

void Graph::allocateVariablesForDFS()
{
	assert(n > 0);
	if (NULL == ccBelongto)
	{
		numChildren = new int[n];
		numNodesSubtree = new int[n];
		parent = new int[n];
		isAP = new bool[n];
		discoveredTime = new int[n];
		lowestTime = new int[n];
		ccBelongto = new int[n];
		lowerBounds = new double[n];
	}

	for (int i = 0; i < n; ++i) // initialize
	{
		// printf("iteration %d\n",i);
		visited[i] = false;
		numChildren[i] = 0;
		numNodesSubtree[i] = 0;
		parent[i] = -1; // -1 indicates that the node is the root
		isAP[i] = false;
		lowerBounds[i] = 0;
	}
	time = 0;

}


void Graph::initilizeVariables()
{
	numChildren = NULL;
	numNodesSubtree = NULL;
	parent = NULL;
	isAP = NULL;
	discoveredTime = NULL;
	lowestTime = NULL;
	ccBelongto = NULL;
	lowerBounds = NULL;
	time = 0;
}

void Graph::clearVariables()
{
	if (NULL != ccBelongto)
	{
		delete []numChildren;
		delete []numNodesSubtree;
		delete []parent;
		delete []isAP;
		delete []discoveredTime;
		delete []lowestTime;
		delete []ccBelongto;
		delete []lowerBounds;
	}
	initilizeVariables();
}

void Graph::findAPsAndLowerBounds()
{
	nonUniformArray allCCs;
	findAllCCsDFS(allCCs);
	int numNodesValid = 0; 
	int i;
	for (i = 0; i < allCCs.size(); ++i)
		numNodesValid += allCCs.size(i);
	allocateVariablesForDFS();
	for (i = 0; i < n; ++i)
	{
		if (false == isValid[i]) continue;
		if (true == visited[i]) continue;
		modifiedDFS(i, allCCs, numNodesValid);
	}
	double base = 0;
	for (i = 0; i < allCCs.size(); ++i)
		base += allCCs.size(i) * (numNodesValid - allCCs.size(i));
	base -= 2 * numNodesValid;
	int numOfAPs = 0;
	for (i = 0; i < n; ++i)
	{
		if (false == isValid[i])continue;
		++numOfAPs;
		lowerBounds[i] += base; 
		lowerBounds[i] *= zeta;
	}
}

int Graph::findAllCCsDFS(nonUniformArray &allCCs)
{
	int i; 
	int numOfCCs = 0;
	sizeofEachCC.clear();
	sizeofEachCC.reserve( 1000 );


	allocateVariablesForDFS();


	int sizeOfCC;
	int maxCCsize = 0;
	for (i = 0; i < n; ++i)
	{
		if (false == isValid[i]) continue;
		if (true == visited[i]) continue;

		sizeOfCC = 0;

		DFS(i, numOfCCs, sizeOfCC); // dfs search

		//assert(sizeOfCC > 0);
		sizeofEachCC.push_back( sizeOfCC );
		++numOfCCs;
		//if ( sizeOfCC >= 30 )   printf("CC %d, size: %d\n", numOfCCs, sizeOfCC);
		if ( sizeOfCC > maxCCsize) maxCCsize = sizeOfCC;
	}
	if (debug) 
		printf("numofCCs: %d, maxCCsize: %d (%.2lf)\n", numOfCCs, maxCCsize, 100.0 * maxCCsize / n);
	
	if (debug)
		for (i = 0; i < n; ++i) printf("node: %d, in CC %d\n", i, ccBelongto[i]);


	allCCs.allocateMemory( sizeofEachCC );

	for (i = 0; i < n; ++i)
	{
		if (false == isValid[i]) continue; 
		allCCs.push_back(ccBelongto[i], i);
	}

	if (debug)
		for (i = 0; i < allCCs.size(); ++i)
		{
			printf("CC %d: ", i);
			for (int j = 0; j < allCCs.size(i); ++j)
				printf("%d ", allCCs.access(i, j ));
			printf("\n");
		}
	return numOfCCs;
}

int Graph::findAllCCsBFS(nonUniformArray &allCCs)
// find all connected components
{
	int i, j;
	int numofCCs = 0;
	sizeofEachCC.clear();
	sizeofEachCC.reserve(1000);

	allocateVariablesForDFS();

	queue_clear();

	int sizeOfCC;
	int maxCCsize = 0;
	int u, v;
	int sz;
	int *adj;
	for (i = 0; i < n; ++i)
	{
		if (true == visited[i]) continue;
		if (false == isValid[i]) continue;

		// search the cc that contains vertex i
		sizeOfCC = 1;
		ccBelongto[ i ] = numofCCs;
		queue_push(i);
		while (queue_size() > 0 )
		{
			u = queue_pop();

			sz = adjLists.size(u);
			adj = & adjLists.access(u, 0);
			for (j = 0; j < sz; ++j)
			{
				v = adj[ j ];
				if (true == visited[v]) continue;
				if (false == isValid[v]) continue;

				queue_push(v);

				visited[ v ] = true;
				ccBelongto[ v ] = numofCCs;
				++sizeOfCC;
			}
		}
		assert(sizeOfCC > 0);

		sizeofEachCC.push_back(sizeOfCC);
		++numofCCs;
		//if ( sizeOfCC > 10 )   printf("CC %d, size: %d\n", numofCCs, sizeOfCC);
		if (sizeOfCC > maxCCsize) maxCCsize = sizeOfCC;
	}
	if (debug)
		printf("numofCCs: %d, maxCCsize: %d (%.2lf)\n", numofCCs, maxCCsize, 100.0 * maxCCsize / n);

	if (debug)
		for (i = 0; i < n; ++i) printf("node: %d, in CC %d\n", i, ccBelongto[i]);

	allCCs.allocateMemory( sizeofEachCC );
	for (i = 0; i < n; ++i)
	{
		if (false == isValid[i]) continue;
		allCCs.push_back(ccBelongto[i], i);
	}

	if (debug)
		for (i = 0; i < allCCs.size(); ++i)
		{
		printf("CC %d: ", i);
		for (int j = 0; j < allCCs.size(i); ++j)
			printf("%d ", allCCs.access(i, j));
		printf("\n");
		}
	return numofCCs;
}


inline void Graph::DFS(int u, int CCID, int & sizeOfCC)
{
	// printf("DFS start search\n");
	visited[u] = true;
	ccBelongto[u] = CCID;
	++sizeOfCC;

	int v;
	int sz = adjLists.size(u);
	int *adj = & adjLists.access(u, 0);
	for (int j = 0; j < sz ; ++j)
	{
		v = adj[ j ];
		//assert(v >= 0 && v < n);

		if (isValid[v] && !visited[v] )
		{
			parent[v] = u;
			DFS(v, CCID, sizeOfCC);
			numNodesSubtree[u] += numNodesSubtree[v];
		}
	}
	++numNodesSubtree[u]; // including itself
}

void Graph::modifiedDFS(int u, nonUniformArray & allCCs, int numNodesValid)
{
	visited[ u ] = true;
	++time;
	discoveredTime[ u ] = lowestTime[ u ] = time;
	//printf("time %d, node %d\n", time, u);
	int ccSize = allCCs.size(ccBelongto[u]);
	int cc0 = ccSize - 1;

	int v;
	int j;
	int sz = adjLists.size(u);
	int *adj = &adjLists.access(u, 0);
	int nv; 
	for (j = 0; j < sz; ++j)
	{
		v = adj[j];
		if (false == isValid[v]) continue;

		if (false == visited[v] )
		{
			parent[ v ] = u;
			++numChildren[ u ];

			modifiedDFS(v, allCCs, numNodesValid);
			numNodesSubtree[u] += numNodesSubtree[v];
			
			if (lowestTime[v] < lowestTime[u])
				lowestTime[u] = lowestTime[v];
			// u is an articulation point in following cases

			// (1) u is root of DFS tree and has two or more chilren.
			if (parent[u] == -1 && numChildren[u] >= 2 ||
				// (2) If u is not root and low value of one of its child
				// is more than discovery value of u.
				parent[u] != -1 && lowestTime[v] >= discoveredTime[u])
			{
				isAP[u] = true;

				nv = numNodesSubtree[v];
				assert(nv < ccSize);
				lowerBounds[u] += nv * ( ccSize - 1 - nv);
				cc0 -= nv;
				assert(cc0 >= 0);
			}
		}
		else if (v != parent[u]) // a back edge is found
		{
			if (discoveredTime[v] < lowestTime[u])
				lowestTime[u] = discoveredTime[v];
		}
	}
	++numNodesSubtree[u]; // including itself

	if (true == isAP[u])
	{
		lowerBounds[u] += cc0 * (ccSize - 1 - cc0); // *zeta;
		lowerBounds[u] += 2 * ccSize;
	}else  // that is the upper bound for non-APs
		lowerBounds[u] = 2 * ccSize + 1; // *zeta;
	
}

void Graph::printGraph()
{
	int i, j;
	for (i = 0; i < n; ++i)
	{
		printf("adjList of node %d: ", i);
		for (j = 0; j < adjLists.size(i); ++j)
			printf("%d,", adjLists.access(i,j) );
		printf("\n");
	}
}

void Graph::cleanGraph(const char *graphFile)
{
	int i, j;
	ifstream in(graphFile);
	if (!in) {
		printf("Graph file `%s' was not found.\n", graphFile);
		return;
	}
	clearGraph();

	in >> n >> m;
	assert(n > 0 && m >= 0);
	assert(n <= MAX_NODES);

	vector<int> degrees; // the degree of each node 
	degrees.resize(n, 0);

	vector<Edge> allEdges;
	allEdges.reserve(m);

	int u, v;
	int numEdges = 0;
	for (i = 0; i < m; ++i)
	{
		if (i % 1000000 == 0) printf("%d (1000,000) th  edge \n", (int)(i / 1000000));

		in >> u >> v;

		if (u == v) {
			printf("A self loop occurs.\n");  
			continue;
		}
		if (u > v) swap(u, v); // make sure that u < v

		if (u < 0 || u >= n){ printf("u exceeds range: %d\n", u); continue; }
		if (v < 0 || v >= n){ printf("v exceeds range: %d\n", v); continue; }

		++degrees[u];
		allEdges.push_back(Edge(u, v));
	}
	in.close();

	adjLists.allocateMemory( degrees );
	for (i = 0; i < allEdges.size(); ++i)
	{
		u = allEdges[i].u;
		v = allEdges[i].v;
		assert(u < v);
		if (true == adjLists.find(u, v)) continue;
		//printf("Parallel edge (%d, %d) occurs\n", u, v); 
		adjLists.push_back(u, v); // insert vertex v to the adjlist of vertex u
		++numEdges;
	}
	printf("number of edges (before): %d, (after): %d\n", m, numEdges);
	m = numEdges;

	char dstFile[100];
	// sprintf_s(dstFile, "datasets/%s", graphFile);
	ofstream out(dstFile);
	if (!out) abort();

	out << n << '\t' << m << '\n';
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < adjLists.size(i); ++j)
			out << i << '\t' << adjLists.access(i,j) << '\n';
	}
	out.close();

	printf("clean finished\n");
}

void Graph::readGraph(const char *graphFile)
{
	// FILE *f; 
	// int err = fopen_s(&f, graphFile, "r");

	// if (err != 0)
	// {
	// 	printf("file: %s was not found!\n", graphFile);
	// 	abort();
	// }
	FILE *f = fopen(graphFile,"r");;

	clearGraph();

	fscanf(f, "%d %d", &n, &m);
	printf("%d %d\n", n, m);
	assert(n > 0 && m >= 0);
	assert(n <= MAX_NODES);

	isValid = new bool[n];
	int i;
	for (i = 0; i < n; ++i) isValid[i] = true;

	vector<Edge> allEdges;
	allEdges.reserve(m);

	vector<int> degrees; // degree of each node
	degrees.resize(n, 0);

	int u, v;
	int numEdges = 0;
	for (i = 0; i < m; ++i)
	{
		if (i % 1000000 == 0 && i > 0 ) printf("%d (1000,000) th  edge \n", (int)(i / 1000000));

		fscanf(f, "%d%d", &u, &v);
		assert(u >= 0 && u < n);
		assert(v >= 0 && v < n);
		++numEdges;

		++degrees[ u ];
		++degrees[ v ];
		allEdges.push_back( Edge(u, v) );
	}
	fclose(f);
	assert(m == numEdges);

	adjLists.allocateMemory(degrees);
	assert( n == adjLists.size() );

	for (i = 0; i < allEdges.size(); ++i)
	{
		u = allEdges[i].u; 
		v = allEdges[i].v;
		adjLists.push_back(u, v);
		adjLists.push_back(v, u);
	}
	printf("graph has been created.\n");
}

void Graph::clearGraph()
{
	if (NULL != isValid)  delete[]isValid;
	isValid = NULL;
	adjLists.clear();
	n = m = 0;
	clearVariables();
}

Graph::Graph()
{
	isValid = NULL;
	n = m = 0;
	debug = false;

	initilizeVariables();
}

Graph::~Graph()
{
	clearGraph();
	clearVariables();
}

Graph::Graph(const Graph &g)
{
	assert(g.n > 0);
	n = g.n; 
	m = g.m;
	adjLists = g.adjLists;
	isValid = new bool[n];
	for (int i = 0; i < n; ++i) isValid[i] = g.isValid[i];
	debug = g.debug;
	
	initilizeVariables();
}

Graph & Graph::operator=(const Graph &g)
{
	if (this == &g) return *this;

	clearGraph();
	clearVariables();

	assert(g.n > 0);
	n = g.n;
	m = g.m;
	adjLists = g.adjLists;

	isValid = new bool[n];
	for (int i = 0; i < n; ++i) isValid[i] = g.isValid[i];
	debug = g.debug;

	initilizeVariables();
	
	return *this;
}



