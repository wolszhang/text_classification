#-----------------------------------------------------------------------#
#																		#
#	python script for Naive Bayes with tf-idf							#
#	sample usage: naive_bayes.py [train] [test]	[word_embedding]		#
#	train:	training document with different labels						#
#	test: testing documents from class1 and class2						#
#	Use sklearn's build-in naive bayes Multinomial implementation		#
#																		#
#	All rights reserved by Yipeng Zhang									#
#-----------------------------------------------------------------------#

import re
import math
import sys
import os
import cPickle
from random import randint
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.naive_bayes import MultinomialNB


def euclideanDistance(instance1, instance2, length):
	distance = 0
	for x in range(length):
		distance += pow((instance1[x] - instance2[x]), 2)
	return math.sqrt(distance)

'''
def nearest_neighbor(word, vec, k):
	neighbor = []
	dist = []
	if '\n' + word in vec:
		for w in vec:
			dis = euclideanDistance(vec['\n'+word], vec[w],len(vec[w]))
			if dis == 0:
				continue
			if len(dist) < k:
				dist.append((w,dis))

			elif dis < dist[k-1]:
				dist.pop()
				dist.append((w,dis))
				dist.sort(key = lambda x:float(x[1]))

	for (w, v) in dist:
		neighbor.append(w)
	return neighbor
'''

def nearest_neighbor(word, vec, k):
	dist_dic = []
	neighbors = []
	for k,v in vec.items():
		ed = euclideanDistance(v,vec['\n'+word],len(v))
		dist_dic.append((k, ed))
	dist_dic.sort(key=lambda tup:tup[1])
	for x in range(k):
		neighbors.append(dist_dic[x])
		print(dist_dic[x])
	return neighbors

if __name__ == "__main__":
	data = []
	target = []	
	test = []
	res = []
	sz1 = sz2  = 0


	with open(sys.argv[3], 'r') as handle:
		vec = cPickle.load(handle)



	word = "happy"
	print(nearest_neighbor(word,vec,3))
'''
	train_file = sys.argv[1]
	for line in open(train_file):
		ind = line.index(' ')
		prefix = line[:ind]
		sentence = ""
		for word in line[ind:].split():
			sentence += word + ' '
			if '\n'+word in vec:
				for w in nearest_neighbor(word, vec):
					sentence += w + ' '
		data.append(sentence)

		if prefix == '1':
			target.append(1)
		else:
			target.append(-1)
		
	
	test_file = sys.argv[2]
	for line in open(test_file):
		ind = line.index(' ')
		prefix = line[:ind]
		test.append(line[ind:])
		if prefix == '1':
			sz1 += 1
			res.append(1)
		else:
			sz2 += 1
			res.append(-1)	


	count_vect = CountVectorizer()
	X_train_counts = count_vect.fit_transform(data)
	tfidf_transformer = TfidfTransformer()
	X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)
	clf = MultinomialNB().fit(X_train_tfidf, target)
	
	X_new_counts = count_vect.transform(test)
	X_new_tfidf = tfidf_transformer.transform(X_new_counts)
	predicted = clf.predict(X_new_tfidf)

	cor1 = 0
	cor2 = 0
	for i in range(0,len(predicted)):
		if predicted[i]==res[i] and res[i]==1:
			cor1 += 1
		if predicted[i]==res[i] and res[i]==-1:
			cor2 += 1
	
	print(predicted)
	print("==================================================")
	print("Current Algorithm: Naive Bayes with tf-idf")
	print("Accuracy for article 1: "+str(100*float(cor1)/sz1)+"%")
	print("Accuracy for article 2: "+str(100*float(cor2)/sz2)+"%")
	print("Overall Accuracy: "+str(100*float(cor2+cor1)/(sz1+sz2))+"%")
'''
	
	