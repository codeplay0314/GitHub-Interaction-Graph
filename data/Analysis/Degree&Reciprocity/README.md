# Analysis: Degree

## Degree Count
### code
`1.count.cpp`
### upstream data
`/data/Graph/G.edgelist`  
### parameter
- **command line**: number of nodes, number of edges, input file, output file  
- **code**: `maxn` number of nodes, `maxm` number of edges
### output
`result.txt`  
```
percentage of balanced nodes  
Top 10 largest incoming degree  
Top 10 smallest incoming degree  
Top 10 largest outgoing degree  
Top 10 smallest outgoing degree  
Top 10 largest total degree  
Top 10 smallest total degree  
```
`degree.txt`: each line with a node's incoming and outgoing degree, seperated by ','

## CCDF of Degree
### code
`2.degree_ccdf.m`
### upstream data
`degree.txt`
### output
CCDF of Degree

## Reciprocity
### code
`3.reciprocity.cpp`
### upstream data
`/data/Graph/G.edgelist`  
### parameter
- **command line**: number of nodes, number of edges, input file, output file  
- **code**: `maxn` number of nodes, `maxm` number of edges
### output
`result.txt`  
```
Reciprocity of the Graph
```
`reciprocity.txt`: each line with a node's reciprocity

## CCDF of Reciprocity
### code
`4.recipro_ccdf.m`
### upstream data
`reciprocity.txt`
### output
CCDF of Reciprocity

## Average Degree and Reciprocity
### code
`5.cal.cpp`
### upstream data
`degree.txt`  
`reciprocity.txt`
### parameter
- **code**: `n` number of nodes
### output
```
average incoming degree
average outgoing degree
average total degree
average reciprocity
```
