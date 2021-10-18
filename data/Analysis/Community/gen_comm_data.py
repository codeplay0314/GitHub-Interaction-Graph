import operator
import numpy, scipy.io
 
with open('graph_node2comm_level2.txt','r') as f1:
	original = f1.read().split('\n')
	data = []
	for item in original:
		a = item.split(' ')
		a = list(map(int, a))
		data.append(a)
	f1.close()

comm = {}
for item in data:
	if item[1] not in comm.keys():
		comm[item[1]] = 1
	else:
		comm[item[1]] += 1
comm = dict(sorted(comm.items(), key=operator.itemgetter(1),reverse=True))
comm = {k:v/1510452 for k, v in comm.items()}
series = list(comm.values())
count = 0 
cumulative = []
for i in series:
	count += i
	cumulative.append(count)
scipy.io.savemat('comm.mat', mdict = {'comm':cumulative})
print(cumulative)
		