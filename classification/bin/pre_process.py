#-----------------------------------------------------------------------#
#																		#
#	python script for data pre-process									#
#	sample usage: pre-process.py [input1] [input2] [output1] [output2]	#
#	input:	input document, a corpus									#
#	output1:test corpus, default to be 33% randomly assigned corpus		#
#	output2:train corpus, default to be 67% randomly assigned corpus	#
#	remove stop words using nltk.stopwords								#
#	adjust proportion variable to set proportion of training vs test	#
#																		#
#	All rights reserved by Yipeng Zhang									#
#-----------------------------------------------------------------------#


import sys
import gensim
from nltk.tokenize import sent_tokenize
from nltk.stem.snowball import PorterStemmer
from nltk.corpus import stopwords
import string 
from random import randint

proportion = 0.33

if __name__ == "__main__":
	if not len(sys.argv)==5:
		print("invalid command line argument. \n Usage: pre-process.py [input1] [input2] [output1] [output2] \n")
		exit(0)

	inp = open(sys.argv[1])
	inp2 = open(sys.argv[2])
	out = open(sys.argv[3],"w")
	out2 = open(sys.argv[4],"w")
	count = 0
	sz = 0
	
	

	data = inp.read()
	sent_tokenize_list = sent_tokenize(unicode(data, errors='ignore'))
	stopWords = set(stopwords.words('english'))
	table = {ord(char): None for char in string.punctuation}
	

	for line in sent_tokenize_list:
		sz += 1
		sys.stdout.write("%d%%\r" % (sz / float(len(sent_tokenize_list)) * 50))
		temp = ""
		for word in line.translate(table).split():
			if word not in stopWords:
				temp += word.lower()+' ';
		
		if len(temp)>=5:
			ran = randint(0,1)

			if count <= proportion*len(sent_tokenize_list) and ran==1:
				count+=1
				out.write('-1 ' +temp+'\n')
			
			else:
				out2.write('-1 ' +temp+"\n")

	sz = 0
	data = inp2.read()
	sent_tokenize_list = sent_tokenize(unicode(data, errors='ignore'))
	stopWords = set(stopwords.words('english'))
	table = {ord(char): None for char in string.punctuation}

	for line in sent_tokenize_list:
		sz += 1
		sys.stdout.write("%d%%\r" % (sz / float(len(sent_tokenize_list)) * 50+50))
		temp = ""
		for word in line.translate(table).split():
			if word not in stopWords:
				temp += word.lower()+' ';
		
		if len(temp)>=5:
			ran = randint(0,1)

			if count <= proportion*len(sent_tokenize_list) and ran==1:
				count+=1
				out.write('1 '+temp+'\n')
			
			else:
				out2.write('1 '+ temp+"\n")
	