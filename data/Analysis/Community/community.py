import networkx as nx
import numpy as np
import json
from matplotlib import pyplot as plt

G = nx.read_edgelist("PR_IC_W_interaction.edgelist", delimiter='	',data=False)
edges = list(G.edges())

edges.sort(key=lambda x: int(x[0]))
with open("graph.txt",'a') as f:
	for edge in edges:
		f.write(edge[0])
		f.write(' ')
		f.write(edge[1])
		f.write('\n')
	f.close()
