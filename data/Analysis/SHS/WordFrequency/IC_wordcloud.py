import json

global false, null, true
false = null = true = ''

f = open('/bdata/yingqiu/IssueCommentEvent.txt','r')

names = {}
for line in f.readlines():
	line = line.strip()
	line = eval(line)
	time = str(line['time'])
	name = time[0:10]+'-'
	if time[11] == '0':
		name += time[12]
	else:
		name += time[11]
		name += time[12]
	names.setdefault(name,[]).append(line['actor'])
f.close()

f = open('/bdata/yingqiu/2020Summer/HIS_login.txt','r')
HIS = []
for line in f.readlines():
	HIS.append(line.strip())
f.close()

SHS = {}
no = {}
for name in names:
	filename = '/bdata/jiayunz/GitHub/GHArchive/2019-03/' + name + '.json'
	cur = open(filename,'r')
	for l in cur.readlines():
		l = json.loads(l)
		if l['type'] == 'IssueCommentEvent' and l['actor']['login'] in names[name]:
			if l['actor']['login'] in HIS:
				try:
					SHS.setdefault(l['actor']['login'],{}).setdefault('Ibody',[]).append(l['payload']['issue']['body'] + ' ')
				except:
					continue
				try:
					SHS.setdefault(l['actor']['login'],{}).setdefault('Cbody',[]).append(l['payload']['comment']['body'] + ' ')
				except:
					continue
				try:
					SHS.setdefault(l['actor']['login'],{}).setdefault('Ititle',[]).append(l['payload']['issue']['title'] + ' ')
				except:
					continue
				try:
					SHS.setdefault(l['actor']['login'],{}).setdefault('CAA',[]).append(l['payload']['comment']['author_association'] + ' ')
				except:
					continue
				if len(l['payload']['issue']['labels']):
					for i in range(0,len(l['payload']['issue']['labels'])):
						SHS.setdefault(l['actor']['login'],{}).setdefault('Ilabel',[]).append(l['payload']['issue']['labels'][i]['name'] + ' ')
			else:
				try:
					no.setdefault(l['actor']['login'],{}).setdefault('Ibody',[]).append(l['payload']['issue']['body'] + ' ')
				except:
					continue
				try:
					no.setdefault(l['actor']['login'],{}).setdefault('Cbody',[]).append(l['payload']['comment']['body'] + ' ')
				except:
					continue
				try:
					no.setdefault(l['actor']['login'],{}).setdefault('Ititle',[]).append(l['payload']['issue']['title'] + ' ')
				except:
					continue
				try:
					no.setdefault(l['actor']['login'],{}).setdefault('CAA',[]).append(l['payload']['comment']['author_association'] + ' ')
				except:
					continue
				if len(l['payload']['issue']['labels']):
					for i in range(0,len(l['payload']['issue']['labels'])):
						no.setdefault(l['actor']['login'],{}).setdefault('Ilabel',[]).append(l['payload']['issue']['labels'][i]['name'] + ' ')

	cur.close()

Ibody_HIS = open('Ibody_HIS_individual.txt','w+')
Cbody_HIS = open('Cbody_HIS_individual.txt','w+')
Ititle_HIS = open('Ititle_HIS_individual.txt','w+')
Ilabel_HIS = open('Ilabel_HIS_individual.txt','w+')
CAA_HIS = open('CAA_HIS_individual.txt','w+')

for key in SHS:
	try:
		for item in SHS[key]['Ibody']:
			Ibody_HIS.write(item.strip())
			Ibody_HIS.write(' ')
		Ibody_HIS.write('\n')
	except:
		continue
	try:
		for item in SHS[key]['Cbody']:
			Cbody_HIS.write(item.strip())
			Cbody_HIS.write(' ')
		Cbody_HIS.write('\n')
	except:
		continue
	try:
		for item in SHS[key]['Ititle']:
			Ititle_HIS.write(item.strip())
			Ititle_HIS.write(' ')
		Ititle_HIS.write('\n')
	except:
		continue
	try:
		for item in SHS[key]['Ilabel']:
			Ilabel_HIS.write(item.strip())
			Ilabel_HIS.write(' ')
		Ilabel_HIS.write('\n')
	except:
		continue
	try:
		for item in SHS[key]['CAA']:
			CAA_HIS.write(item.strip())
			CAA_HIS.write(' ')
		CAA_HIS.write('\n')
	except:
		continue

Ibody_HIS.close()
Cbody_HIS.close()
Ititle_HIS.close()
Ilabel_HIS.close()
CAA_HIS.close()

Ibody = open('Ibody_individual.txt','w+')
Cbody = open('Cbody_individual.txt','w+')
Ititle = open('Ititle_individual.txt','w+')
Ilabel = open('Ilabel_individual.txt','w+')
CAA = open('CAA_individual.txt','w+')

for key in no:
	try:
		for item in no[key]['Ibody']:
			Ibody.write(item.strip())
			Ibody.write(' ')
		Ibody.write('\n')
	except:
		continue
	try:
		for item in no[key]['Cbody']:
			Cbody.write(item.strip())
			Cbody.write(' ')
		Cbody.write('\n')
	except:
		continue
	try:
		for item in no[key]['Ititle']:
			Ititle.write(item.strip())
			Ititle.write(' ')
		Ititle.write('\n')
	except:
		continue
	try:
		for item in no[key]['Ilabel']:
			Ilabel.write(item.strip())
			Ilabel.write(' ')
		Ilabel.write('\n')
	except:
		continue
	try:
		for item in no[key]['CAA']:
			CAA.write(item.strip())
			CAA.write(' ')
		CAA.write('\n')
	except:
		continue

Ibody.close()
Cbody.close()
Ititle.close()
Ilabel.close()
CAA.close()
