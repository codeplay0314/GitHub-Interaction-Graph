import random
from nltk.corpus import stopwords
from wordcloud import WordCloud
import matplotlib.pyplot as plt

filenames = ['Cbody','Ibody','Ilabel','Ititle','CAA']

def gettext(n):
	txt = open(n,"r",errors='ignore').read()
	txt = txt.lower()
	for ch in '!"#$&()*+,-./:;<=>?@[\\]^_{|}·~‘’':
		txt = txt.replace(ch,"")
	return txt

w = open('/bdata/yingqiu/word_cloud/word_frequency.txt','a')
w.write('\n')
w.write('INDIVIDUAL')
w.write('\n')

for filename in filenames:
	name = '/bdata/yingqiu/word_cloud/every_user/' + filename + '_individual.txt'
	text = gettext(name)
	text = text.split()
	counts = {}
	cnt = 0
	for word in text:
		counts[word] = counts.get(word,0) + 1
		cnt += 1
	print('READ')
	items = list(counts.items())
	items.sort(key=lambda x:x[1],reverse=True)
	w.write(filename)
	w.write(':\n')
	w.write(str(cnt))
	w.write('\n')
	x = 0
	for i in range(20):
		try:
			while x >= 0:
				word,count = items[i + x]
				if word not in stopwords.words('english'):
					w.write("{0:<10}{1:>5}".format(word,count))
					w.write('\n')
					break
				else:
					x += 1
		except:
			continue
	w.write('\n')
	name = '/bdata/yingqiu/word_cloud/every_user/' + filename + '_HIS_individual.txt'
	text = gettext(name)
	text = text.split()
	counts = {}
	cnt = 0
	for word in text:
		counts[word] = counts.get(word,0) + 1
		cnt += 1
	print('READ')
	items = list(counts.items())
	items.sort(key=lambda x:x[1],reverse=True)
	w.write(filename)
	w.write('_HIS:\n')
	w.write(str(cnt))
	w.write('\n')
	x = 0
	for i in range(20):
		try:
			while x >= 0:
				word,count = items[i + x]
				if word not in stopwords.words('english'):
					w.write("{0:<10}{1:>5}".format(word,count))
					w.write('\n')
					break
				else:
					x += 1
		except:
			continue
	w.write('\n')

w.close()
