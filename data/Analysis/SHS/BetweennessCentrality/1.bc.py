import networkx as nx
import numpy as np
import time

print(time.time(), "ok")
input = open("G.edgelist", "r")

G = nx.DiGraph()
for line in input:
    e = line.strip().split('\t')
    G.add_edge(int(e[0]), int(e[1]))

print(time.time(), "ok")
BC = nx.betweenness_centrality(G, k = 10000)
print(time.time(), "ok")
n = G.number_of_nodes()

output = open("bc.txt", "w")
for i in range(n):
    print(BC[i], file = output)