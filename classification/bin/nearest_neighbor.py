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

from __future__ import division
import struct
import sys
import cPickle
import math


def euclideanDistance(instance1, instance2, length):
	distance = 0
	for x in range(length):
		distance += pow((instance1[x] - instance2[x]), 2)
	return math.sqrt(distance)



if __name__ == "__main__":
	
	with open('vectors.pcl', 'rb') as handle:
		vec = cPickle.load(handle)
	
	print(len(vec))
	while(True):
		nn = int(raw_input("number of neighbors: "))
		word = raw_input("query word: ")

		if '\n'+word not in vec:
			print("word "+ word+ " not found")
			continue

		dist_dic = []
		neighbors = []
		for k,v in vec.items():
			ed = euclideanDistance(v,vec['\n'+word],len(v))
			dist_dic.append((k, ed))
		dist_dic.sort(key=lambda tup:tup[1])
		for x in range(nn):
			neighbors.append(dist_dic[x])
			print(dist_dic[x])
