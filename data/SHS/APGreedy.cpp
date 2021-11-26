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
	void findTopkHolesByAPGreedy(int K);
public:
	Graph originalGraph;
protected:
	void removeOneVertex(Graph &Gi, int u);
};

int main(const int argc, const char *argv[])
{ 
	char testFileName[50] = "holes/datasets/dblp.txt";
	srand(1); 
	Hole hole;
	hole.readGraph(testFileName);
	const int K = 100; // number of holes
	vector<int> foundHoles;
	vector<double> foundTimes;
	clock_t st = clock();
	hole.findTopkHolesByAPGreedy(K);
	printf("time: %.2lf (s)\n", (clock() - st)/1000000.0 );	
	printf("timeALG: %.2lf (s)\n", timeAlg / 1000.0);
	return 0;
	
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

void Hole::findTopkHolesByAPGreedy(int K)
{

	ofstream f1("APGreedy.txt");
	printf("find top holes apgreedy:%d %d\n",K,originalGraph.n);
	assert(K > 0 && K <= originalGraph.n);
	clock_t st = clock();


	Graph Gi = originalGraph;
	int i, j;

	/*bool test = true;
	while (test) // lambda core
	{
		test = false;
		for (i = 0; i < Gi.n; ++i)
		{
			if (false == Gi.isValid[i]) continue;
			if (Gi.adjLists.size(i) >= lambda) continue;
			test = true;
			removeOneVertex(Gi, i);
		}
	}*/

	int n = originalGraph.n;
	int hole;
	double maxLBAPs;
	double maxUBnonAPs;
	printf("Start k holes!\n");
	for (i = 0; i < K; ++i)
	{
		/*
		try
		{
			Gi.findAPsAndLowerBounds();
		}
		catch(std::bad_alloc)
		{
		    cout << ""; 
		}
		*/
		Gi.findAPsAndLowerBounds();
		maxLBAPs = 0;
		for (j = 0; j < n; ++j)
		{
			if (false == Gi.isValid[j])continue;
			if (false == Gi.isAP[j]) continue;
			if (Gi.lowerBounds[j] > maxLBAPs)
			{
				maxLBAPs = Gi.lowerBounds[j];
				hole = j;
			}
		}

		//maxUBnonAPs = computeMaxUpperBoundforNonAPs(Gi);
		
		//if (maxUBnonAPs > maxLBAPs) abort();
			//cout << i << ", maxUBnonAPs: " << maxUBnonAPs << ", maxLBAPs: " << maxLBAPs << endl;

		/*nonUniformArray allCCs;
		Gi.findAllCCsDFS( allCCs );
		int maxCCid, maxCC = 0;
		for (j = 0; j < allCCs.size(); ++j)
		{
			if (allCCs.size(j) > maxCC)
			{
				maxCCid = j;
				maxCC = allCCs.size(j);
			}
		}	
		
		if (Gi.ccBelongto[hole] != maxCCid)
		{
			cout << i << ", node: " << hole << ",\tmaxlb: " << maxLBAPs << endl;
			printf("-------in CC %d, max CCid: %d, %s\n", Gi.ccBelongto[hole], maxCCid, Gi.ccBelongto[hole] == maxCCid ? "yes" : "nooooooooooooooo");
		}*/
		
		removeOneVertex(Gi, hole);
		printf("found %d th hole: %d\n", i + 1, hole);
		f1 << hole << endl;
	}
	f1.close();
}

void Hole::removeOneVertex(Graph &Gi, int u)
{
	assert(true == Gi.isValid[u]);
	int j;
	int v;
	for (j = 0; j < Gi.adjLists.size(u); ++j)
	{
		v = Gi.adjLists.access(u,j);
		Gi.adjLists.erase(v, u);
	}

	Gi.adjLists.clear( u ); // clear 
	Gi.isValid[u] = false;
}

