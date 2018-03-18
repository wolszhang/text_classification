import re
import sys
import os
from random import randint
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.naive_bayes import MultinomialNB
from sklearn.datasets import fetch_20newsgroups

if __name__ == "__main__":
	count_vect = CountVectorizer()
	inp = sys.argv[1]
	data = []
	target = []

	for line in open(inp):
		data.append(line)
		target.append(1)

	inp = sys.argv[2]
	for line in open(inp):
		data.append(line)
		target.append(0)
		
	X_train_counts = count_vect.fit_transform(data)
	tfidf_transformer = TfidfTransformer()
	X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)
	clf = MultinomialNB().fit(X_train_tfidf, target)
	clf2 = MultinomialNB().fit(X_train_counts, target)
	outp = sys.argv[3]
	test = []
	res = []
	sz1 = 0
	sz2 = 0
	for line in open(outp):
		test.append(line)
		res.append(1)
		sz1 += 1
	outp = sys.argv[4]
	for line in open(outp):
		test.append(line)
		res.append(0)
		sz2 += 1
	X_new_counts = count_vect.transform(test)
	X_new_tfidf = tfidf_transformer.transform(X_new_counts)
	predicted = clf.predict(X_new_tfidf)
	predicted2 = clf2.predict(X_new_counts)

	cor1 = 0
	cor2 = 0
	for i in range(0,len(predicted2)):
		if predicted[i]==res[i] and res[i]==1:
			cor1 += 1
		if predicted[i]==res[i] and res[i]==0:
			cor2 += 1
	print("==================================================")
	print("Current Algorithm: Naive Bayes")
	print("majority vote accuracy for article 1: "+str(100*float(cor1)/sz1)+"%")
	print("acc1: "+str(cor1)+" sz1: "+str(sz1))
	print("majority vote accuracy for article 2: "+str(100*float(cor2)/sz2)+"%")
	print("acc2: "+str(cor2)+" sz2: "+str(sz2))
	cor1 = 0
	cor2 = 0
	for i in range(0,len(predicted)):
		if predicted[i]==res[i] and res[i]==1:
			cor1 += 1
		if predicted[i]==res[i] and res[i]==0:
			cor2 += 1
	
	print("==================================================")
	print("Current Algorithm: Naive Bayes with tf-idf")
	print("majority vote accuracy for article 1: "+str(100*float(cor1)/sz1)+"%")
	print("acc1: "+str(cor1)+" sz1: "+str(sz1))
	print("majority vote accuracy for article 2: "+str(100*float(cor2)/sz2)+"%")
	print("acc2: "+str(cor2)+" sz2: "+str(sz2))