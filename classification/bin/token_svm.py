#-----------------------------------------------------------------------#
#																		#
#	python script for token level classification						#
#	sample usage: token_svm.py [-h] [-s] [-w] [-train TRAIN]			#
#   [-test TEST] [-model MODEL] [-save SAVE] [-emb EMB]					#
#	 																	#
#   python token_svm.py -h for more information about input command 	#
#	using a pre-trained models or input files to train a svm classifier	#
#	based on the selected token level (word level by default)			#
#																		#
#	All rights reserved by Yipeng Zhang									#
#																		#
#-----------------------------------------------------------------------#
#python token_svm.py -emb vectors.pcl -train ../train -test ../test 

from __future__ import division
import argparse

import struct
import sys
import cPickle
import math
from sklearn import svm
from sklearn.externals import joblib

def euclideanDistance(instance1, instance2, length):
	distance = 0
	for x in range(length):
		distance += pow((instance1[x] - instance2[x]), 2)
	return math.sqrt(distance)


def voting(votes, truth):
	cor1 = cor2 = sz1 = sz2 = 0
	for i in range(len(votes)):
		res = 0
		for vote in votes[i]:
			res += vote
			if truth[i] == 1:
				sz1 += 1
				if res > 0:
					cor1 += 1
			elif truth[i] == -1:
				sz2 += 1
				if res < 0:
					cor2 += 1

	return cor1, cor2, sz1, sz2


if __name__ == "__main__":
	parser = argparse.ArgumentParser(description='token level classification.')
	parser.add_argument('-s', "--sentence_level",
		help='sentence-level classification', action="store_true")
	parser.add_argument('-w', "--word_level", 
		help='word-level classification', action="store_true")
	parser.add_argument("-train","--train", help=' train file location')
	parser.add_argument('-test','--test', help=' test file location')
	parser.add_argument('-model','--model', help=' model file location')
	parser.add_argument('-save','--save', help=' save model file location')
	parser.add_argument('-emb','--emb', help=' word embedding file location')
		
	args = parser.parse_args()
	
	if args.emb == None:
		print("Token level classification requires pre-trained embeddings. ")
		print("python token_svm.py -help for more info")
		exit(1)
	with open(args.emb, 'r') as handle:
		vec = cPickle.load(handle)

	# dealing with training files
	vector_array = []
	label_array = []
	if args.train:
		train_file = open(args.train, 'rb')
		if not args.sentence_level:
			for line in train_file:
				label = int(line.split()[0])
				for word in line.split()[1:]:
					if '\n'+word in vec:
						vector_array.append(vec['\n'+word])
						label_array.append(label)

	svm_classifier = svm.SVC()
	svm_classifier.fit(vector_array, label_array)

	if args.save:
		joblib.dump(svm_classifier, args.save+'.pkl')

	if args.model:
		svm_classifier = joblib.load(args.model+'.pkl')

	if args.test:
		test_file = open(args.test, 'rb')
		votes = []
		label = []
		if not args.sentence_level:
			for line in test_file:
				label.append(int(line.split()[0]))
				vote = []
				test_set = []
				for word in line.split()[1:]:
					if '\n'+word in vec:
						test_set.append(vec['\n'+word])
				votes.append(svm_classifier.predict(test_set))

		cor1, cor2, sz1, sz2 = voting(votes, label)	
		print("==================================================")
		print("Current Algorithm: SVM word level classification")
		print("Accuracy for article 1: "+str(100*float(cor1)/sz1)+"%")
		print("Accuracy for article 2: "+str(100*float(cor2)/sz2)+"%")
		print("Overall Accuracy: "+str(100*float(cor1+cor2)/(sz1+sz2))+"%")
		
