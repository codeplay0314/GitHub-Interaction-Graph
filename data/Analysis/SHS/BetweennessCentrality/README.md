# Analysis of SHS: Betweenness Centrality

## Calculation 
### code
`1.bc.py`  
- calculate the approximate betweenness centrality of each code
### upstream data
`/data/Graph/G.edgelist`  
`/data/Analysis/louvain.txt`
### parameter
- **code**: `maxn` number of nodes, `maxm` number of edges
### output
`num_connected_community.txt`

## Plotting
### code
`2.community_ccdf.m`
### upstream data
`num_connected_community.txt`
### output
`bc_k10000.png`