# Analysis: Degree

## Strongly Connected Component
### code
`1.find_scc.cpp`  
- algorithm: Tarjan
### upstream data
`/data/Graph/G.edgelist`  
### parameter
- **command line**: number of nodes, number of edges, input file, output file  
- **code**: `maxn` number of nodes, `maxm` number of edges
### output
```
number of SCC
top 10 SCCs
```
`scc.txt`: the i th line gives a number representing the index of the strongly connected component of the i th node
### sample
```
g++ 1.find_scc.cpp -o scc
./scc 6012074 42700112 G.edgelist scc.txt

There are 5560135 components.
Top components: 420124 55 53 44 39 39 38 32 30 27
```

## Weekly Connected Component
### code
`2.find_wcc.cpp`
- algorithm: union find
### upstream data
`/data/Graph/G.edgelist`  
### parameter
- **command line**: number of nodes, number of edges, input file, output file  
- **code**: `maxn` number of nodes, `maxm` number of edges
### output
```
number of WCC
top 10 WCCs
```
`wcc.txt`: the i th line gives a number representing the index of the weekly connected component of the i th node
### sample
```
g++ 2.find_wcc.cpp -o wcc
./wcc 6012074 42700112 G.edgelist wcc.txt

There are 91253 components.
Top components: 5796408 54 50 49 46 46 44 42 41 36
```

## Largest SCC
### code
`3.cal.cpp`
### upstream data
`scc.txt`  
### paramete
- **code**: `n` number of nodes
### output
`result.txt`: the index of the largest SCC
### sample
```
LSCC: 409858
```