#-----------------------------------------------------------------------#
#																		#
#	python script for Naive Bayes with tf-idf							#
#	sample usage: naive_bayes.py [train] [test]							#
#	train:	training document with different labels						#
#	test: testing documents from class1 and class2						#
#	Use sklearn's build-in naive bayes Multinomial implementation		#
#																		#
#	All rights reserved by Yipeng Zhang									#
#-----------------------------------------------------------------------#

import re
import sys
import os
from random import randint
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.naive_bayes import MultinomialNB

if __name__ == "__main__":
	data = []
	target = []	
	test = []
	res = []
	sz1 = sz2  = 0

	train_file = sys.argv[1]
	for line in open(train_file):
		ind = line.index(' ')
		prefix = line[:ind]
		data.append(line[ind:])
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
	