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
	
	outp = sys.argv[3]
	test = []

	for line in open(inp):
		test.append(line)

	outp = sys.argv[4]
	for line in open(inp):
		test.append(line)

	X_new_counts = count_vect.transform(test)
	X_new_tfidf = tfidf_transformer.transform(X_new_counts)
	predicted = clf.predict(X_new_tfidf)
	print(len(predicted))
