#include <iostream>
#include<assert.h>
#include<map>
#include <math.h>  
#include "graph.h"
using namespace std;

const int MAX_EDGES = 428551285+5;

inline bool compLess(Node & a, Node & b) // operator <
{
	return a.key < b.key;
}

class Hole{ // Structural hole spanner
public:
	void readGraph(const char *graphFile);
	void findTopkHolesByConstraint(int K, vector<int> & foundHoles, vector<double> &foundTimes);
public:
	Graph originalGraph;
};

int main(const int argc, const char *argv[])
{ 
	char testFileName[50] = "graph.txt";
	srand(1); 
	Hole hole;
	hole.readGraph(testFileName);
	const int K = 10000; // number of holes
	vector<int> foundHoles;
	vector<double> foundTimes;
	clock_t st = clock();
	hole.findTopkHolesByConstraint(K, foundHoles, foundTimes);
	printf("time: %.2lf (s)\n", (clock() - st)/1000000.0 );	
	printf("timeALG: %.2lf (s)\n", timeAlg / 1000.0);
	return 0;
	
}

void Hole::findTopkHolesByConstraint(int K, vector<int> & foundHoles, vector<double> &foundTimes)
{ // score nodes by Burt's constraint, the value of local constraint c(u,v) of two neighbors u and v is c(u,v) = ( p_u,v + \sum_w\in N(v) p_u,w * p w, v ) ^2
// and c(u) = \sum_v\in N(u) c(u,v), p(u,v) = 1.0 / N(u). 
	assert(K > 0);
	if (K > originalGraph.n) K = (originalGraph.n + 1) / 2;
	foundHoles.clear();
	foundHoles.reserve(K);
	foundTimes.clear();
	foundTimes.reserve(K);
	clock_t st = clock();
	int n = originalGraph.n;
	vector<Node> constraints;
	int u, v, w;
	int i, j;
	int degree_u;
	int degree_w;
	double c_u, c_uv;
	bool *isCommonNeighbors = new bool[n];
	for (u = 0; u < n; ++u) isCommonNeighbors[u] = false;
	bool vb = false;
	for (u = 0; u < n; ++u)
	{
		degree_u = originalGraph.adjLists.size(u);
		if (0 == degree_u) // assign a large value to an isolated node
		{
			constraints.push_back(Node(u, n));
			continue;
		}
		c_u = 0;
		for (i = 0; i < originalGraph.adjLists.size(u); ++i) // record node u's neighbors
		{
			v = originalGraph.adjLists.access(u, i);
			isCommonNeighbors[v] = true;
		}
		
		if ( vb )	printf("node %d ----------------------\n", u);
		for (i = 0; i < originalGraph.adjLists.size(u); ++i) // for each of u's neighbors
		{
			v = originalGraph.adjLists.access(u, i);
			c_uv = 1.0 / degree_u; // p_u,v
			for (j = 0; j < originalGraph.adjLists.size(v); ++j) // for each of v's neighbors
			{
				w = originalGraph.adjLists.access(v, j);
				if (true == isCommonNeighbors[w]) // w is a common neighbor of nodes u and v
				{
					degree_w = originalGraph.adjLists.size(w);
					assert(degree_w > 0);
					c_uv += (1.0 / degree_u) * (1.0 / degree_w);
				}
			}
			if (vb) printf("c_%d,%d: %.4lf\n", u, v, c_uv);
			c_uv = c_uv * c_uv; // the square
			c_u += c_uv;
		}
		constraints.push_back(Node(u, c_u));
		if (vb) printf("node %d, constraint: %.4lf\n\n", u, c_u);
		
		for (i = 0; i < originalGraph.adjLists.size(u); ++i)
		{
			v = originalGraph.adjLists.access(u, i);
			isCommonNeighbors[v] = false; //reset
		}
	}
	sort(constraints.begin(), constraints.end(), compLess);
	
	FILE *f = fopen("Constraint.txt","w");
	for (i = 0; i < K; ++i){
		foundHoles.push_back(constraints[i].id); 
		printf("found %d th hole: %d\n", i + 1, constraints[i].id);
		fprintf(f,"%d %f\n",  constraints[i].id, constraints[i].key);
	}

	double duration = double(clock() - st) / CLOCKS_PER_SEC; // seconds
	foundTimes.resize(K, duration);

	delete []isCommonNeighbors;
}

void Hole::readGraph(const char *graphFile)
{
	originalGraph.clearGraph();
	originalGraph.clearVariables();

	originalGraph.readGraph(graphFile);
	double n = originalGraph.n;
	zeta = n * n * n / 3.0;
	//zeta = 3 * n;
}



