import sys
import gensim
from nltk.tokenize import sent_tokenize
from nltk.stem.snowball import PorterStemmer
from nltk.corpus import stopwords
import string 
from random import randint

if __name__ == "__main__":
	if (len(sys.argv)<3 or len(sys.argv)>4):
		print("invalid command line argument. \n Usage: cut.py [input] [output1] [output2] \n")
		exit(0)

	inp = open(sys.argv[1])
	out = open(sys.argv[2],"w")
	out2 = open(sys.argv[3],"w")
	count = 0
	
	
	data = inp.read()
	sent_tokenize_list = sent_tokenize(unicode(data, errors='ignore'))
	stopWords = set(stopwords.words('english'))
	table = {ord(char): None for char in string.punctuation}
	sz = 0
	for line in sent_tokenize_list:
		sz = sz +1 

	for line in sent_tokenize_list:
		temp = ""
		for word in line.translate(table).split():
			if word not in stopWords:
				temp += word.lower()+' ';
		if len(temp)>=5:
			ran = randint(0,1)
			if count <= sz/3 and ran==1:
				count+=1
				out.write(temp+'\n')
			else:
				out2.write(temp+"\n")
	count =0