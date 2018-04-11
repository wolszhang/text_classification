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

	vector_array = [[1,1], [0,0]]
	label_array = [1, -1]
	svm_classifier = svm.SVC()
	svm_classifier.fit(vector_array, label_array)

	
	res = svm_classifier.predict([[0.7,0.9], [0.1,-0.2]])
	sum = 0
	print(res)
	for i in res:
		sum += i
	print(sum)
	print( int(-1))