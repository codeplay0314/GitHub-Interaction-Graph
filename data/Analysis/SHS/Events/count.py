import json
import time

fhand = open("WatchEvent.txt", 'r', encoding = 'UTF-8')

node = 0
names = dict()
list1 = dict()
list2 = dict()

for line in fhand:
    event = json.loads(line)
    nodeu = event["repo"].split('/')[0]
    nodev = event["actor"]
    t = time.mktime(time.strptime(event["time"], "%Y-%m-%dT%H:%M:%SZ"))
    if names.get(nodeu) is None:
        names[nodeu] = node
        list1[node] = list()
        list2[node] = list()
        node = node + 1
    if names.get(nodev) is None:
        names[nodev] = node
        list1[node] = list()
        list2[node] = list()
        node = node + 1
    list1[names[nodeu]].append(t)
    list2[names[nodev]].append(t)

file1 = open("eventsum.txt_in", 'w', encoding = 'UTF-8')
file2 = open("eventsum_shs_con_in.txt", 'w', encoding = 'UTF-8')
file3 = open("eventsum_shs_his_in.txt", 'w', encoding = 'UTF-8')
file4 = open("eventsum_out.txt", 'w', encoding = 'UTF-8')
file5 = open("eventsum_shs_con_out.txt", 'w', encoding = 'UTF-8')
file6 = open("eventsum_shs_his_out.txt", 'w', encoding = 'UTF-8')
file7 = open("eventinterval_in.txt", 'w', encoding = 'UTF-8')
file8 = open("eventinterval_shs_con_in.txt", 'w', encoding = 'UTF-8')
file9 = open("eventinterval_shs_his_in.txt", 'w', encoding = 'UTF-8')
file10 = open("eventinterval_out.txt", 'w', encoding = 'UTF-8')
file11 = open("eventinterval_shs_con_out.txt", 'w', encoding = 'UTF-8')
file12 = open("eventinterval_shs_his_out.txt", 'w', encoding = 'UTF-8')

f1 = open("Constraint_login.txt", 'r', encoding = 'UTF-8')
f2 = open("HIS_login.txt", 'r', encoding = 'UTF-8')
CON = dict()
HIS = dict()

for line in f1:
    login = line.split()[0]
    CON[login] = 1
for line in f2:
    login = line.split()[0]
    HIS[login] = 1

for name, n in names.items():
    if list1.get(n) is not None: sz = len(list1[n])
    else: sz = 0
    print(sz, file = file1)
    if CON.get(name) is not None: print(sz, file = file2)
    if HIS.get(name) is not None: print(sz, file = file3)
    if sz > 1:
        res = (list1[n][sz - 1] - list1[n][0]) / (sz - 1)
        print(res, file = file7)
        if CON.get(name) is not None: print(res, file = file8)
        if HIS.get(name) is not None: print(res, file = file9)

    if list2.get(n) is not None: sz = len(list1[n])
    else: sz = 0
    sz = len(list2[n])
    print(sz, file = file4)
    if CON.get(name) is not None: print(sz, file = file5)
    if HIS.get(name) is not None: print(sz, file = file6)
    if sz > 1:
        res = (list2[n][sz - 1] - list2[n][0]) / (sz - 1)
        print(res, file = file10)
        if CON.get(name) is not None: print(res, file = file11)
        if HIS.get(name) is not None: print(res, file = file12)
