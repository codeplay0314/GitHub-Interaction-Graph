import json
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

global false, null, true
false = null = true = ''

G = nx.read_edgelist("PR_IC_W_interaction.edgelist", delimiter='	', data = False, create_using=nx.DiGraph())
ordinary = list(G.nodes())
print(G.number_of_edges())



f = open('/bdata/yingqiu/2020Summer/HIS_login.txt','r')
HIS = []
for line in f.readlines():
	HIS.append(line.strip())
f.close()

SHS = pd.DataFrame(columns = ['login','followers','followings','public repos'])
no = pd.DataFrame(columns = ['login','followers','followings','public repos'])

f = open('/bdata/yingqiu/2020Summer/AllUsersInfo.txt','r')
for line in f.readlines():
    l = eval(line)
    if l['login'] in HIS:
		try:
            SHS = SHS.append(pd.DataFrame({'login':l['login'],'followers':l['followers'],'followings':l['following'],'public repos':l['public_repos']}, index = [1]),ignore_index=True)
        except:
            continue
    else:
        try:
            no = no.append(pd.DataFrame({'login':l['login'],'followers':l['followers'],'followings':l['following'],'public repos':l['public_repos']},index = [1]),ignore_index=True)
        except:
            continue
f.close()

SHS.to_csv('SHS_bar.csv', index = None)
no.to_csv('ordinary_bar.csv', index = None)
x = np.linspace(1, 4, 3)
labels = ['followers','followings','public repos']
noHIS_data = [no['followers'].mean(), no['followings'].mean(), no['public repos'].mean()]
HIS_data = [SHS['followers'].mean(), SHS['followings'].mean(), SHS['public repos'].mean()]
print(no.head())
print(SHS.head())
print(noHIS_data)
print(HIS_data)
plt.figure(figsize=(20, 10))
plt.bar(x,noHIS_data,width = 0.3,label = 'Ordinary Users',color = 'royalblue')
plt.bar(x + 0.5,HIS_data,width = 0.3,label = 'SHS',color = 'coral')
plt.xticks(x + 0.25, labels)
plt.tick_params(labelsize = 16)
plt.ylabel('User Average',fontsize = 18)
#plt.xlabel('Profile Fields',fontsize = 18)
sns.set(style = 'darkgrid')
plt.rcParams['font.sans-serif']=['Microsoft YaHei']
plt.legend(fontsize = 18)
plt.show()
plt.savefig('average_bar.png')