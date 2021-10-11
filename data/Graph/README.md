# Interaction Graph Building (data/Graph)

Due to extremely large size, the data are stored at server `10.176.122.43:~/GitHub-Interaction-Graph/Graph` as `G.edgelist`.

## Source
- upstream data: `data/GHArchive`  
- generating program: `getTargetEvent.py`
- parameter  
  `targetEvents`: chosen GitHub Events to build interaction graph on

## Size
636M

## Format
In `G.edgelist`, each line contains two integers, which represent an edge in the interaction graph by giving the orders of two nodes.  
The nodes are indexed from 0 continuously.