# Analysis: Degree

## Rebuild 
### code
`1.rebuild.cpp`  
- aggregate nodes in a same strongly connected component
### upstream data
`/data/Graph/G.edgelist`  
`/data/Analysis/ConnectedComponent/scc.txt`  
### parameter
- **command line**: number of nodes, number of edges, number of strongly connected components, input file, output file  
- **code**: `maxn` number of nodes, `maxm` number of edges
### output
`NewGraph.txt`: the first line containts two integers, which are the number of nodes and edges of the new graph, respectively. Following lines each represents a line giving the indices of two nodes of an edge in the graph and its weight(how many edges were in the orginal graph connecting these two components).
### sample
```
g++ 1.rebuild.cpp -o rebuild
./rebuild 6012074 42700112 5560135 G.edgelist NewGraph.txt
```

## DFS for mark
### code
`2.dfs.cpp`
- mark each node in the new graph by the definition of macrostrucure(see: M. Gabielkov, A. Rao, and A. Legout, “Studying social networksat scale: macroscopic anatomy of the twitter social graph,” in ACMSIGMETRICS, 2014.)
### upstream data
`NewGraph.txt`  
### parameter
- **code**: `root`: lscc calculated in previous procedure, `maxn` number of nodes, `maxm` number of edges
### output
`scctype.txt`: the i th line gives two integers, which the first gives the class the i th node should be according to macrostructure

## Macrostructure
### code
`3.calc.cpp`
### upstream data
`/data/Graph/G.edgelist`  
`/data/Analysis/ConnectedComponent/scc.txt`  
`scctype.txt`
### paramete
- **command line**: number of nodes, number of edges, number of strongly connected components, input file, output file  
### output
`macro.txt`: the macrostructure of the interaction graph (node and edge weights included)
### sample
```
g++ 3.calc.cpp -o calc
./calc 6012074 42700112 5560135 G.edgelist macro.txt

NODES:
DISCONNECTED: 4355
LSCC: 420124
OUT: 411707
IN: 2570979
BRIDGES: 143181
IN-TENDRILS: 663803
OUT-TENDRILS: 1436564
OTHER: 361361

EDGES:
LSCC -> OUT: 6348674
IN -> LSCC: 13344126
IN -> IN-TENDRILS: 810271
OTHER -> IN-TENDRILS: 109432
OUT-TENDRILS -> OTHER: 29129
IN -> BRIDGES: 187101
IN -> OUT: 11939050
BRIDGES -> IN-TENDRILS: 15215
OUT-TENDRILS -> IN-TENDRILS: 30019
BRIDGES -> OUT: 222564
OUT-TENDRILS -> OUT: 1886034
OUT-TENDRILS -> BRIDGES: 26378

```