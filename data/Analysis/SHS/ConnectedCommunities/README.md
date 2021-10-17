# Analysis of SHS: Connected Communities

## Calculation 
### code
`1.cc.cpp`  
- calculate the number of communities found by the Louvain algorithm that each code connects
### upstream data
`/data/Graph/G.edgelist`  
### parameter
- **code**: `maxn` number of nodes, `maxm` number of edges, `k`: the approximation parameter, bigger one results higher approximation
### output
`bc.txt`: the approximate betweenness centrality of each node  
the file are divided into different groups, bc of ordinary users and SHS users, according to Constraint and HIS respectively

## Plotting
### code
`2.bc_ccdf.cpp`
### upstream data
`bc_*.txt`
### output
`degree_ccdf.png`