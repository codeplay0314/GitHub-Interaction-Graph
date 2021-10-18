import numpy, scipy.io
import networkx as nx
import operator

G = nx.read_edgelist("PR_IC_W_interaction.edgelist", delimiter='	',data=False,create_using=nx.DiGraph())
coefficient = list(nx.clustering(G).values())
cc = {}
for item in coefficient:
	if item not in cc.keys():
		cc[item] = 1
	else:
		cc[item] += 1
cc = dict(sorted(cc.items(), key=operator.itemgetter(0)))
count = 0 
cumulative = []
for i in cc.values():
	count += i
	cumulative.append(count)

scipy.io.savemat('cc_x.mat', mdict = {'cc_x':cc.keys()})
scipy.io.savemat('cc_y.mat', mdict = {'cc_y':cumulative})