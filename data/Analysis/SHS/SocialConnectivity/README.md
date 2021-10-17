# Analysis of SHS: Social Connectivity

## Calculation 
### code
`1.cal.cpp`  
- calculate the social connectivity data of each code
### upstream data
`/data/Graph/G.edgelist`  
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
`num_com.png`