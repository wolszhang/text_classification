#-----------------------------------------------------------------------#
#																		#
#	python script for token level classification						#
#	sample usage: pre-process.py [input] [output1] [output2]			#
#	input:	input document, a corpus									#
#	output1:test corpus, default to be 33% randomly assigned corpus		#
#	output2:train corpus, default to be 67% randomly assigned corpus	#
#	remove stop words using nltk.stopwords								#
#	adjust proportion variable to set proportion of training vs test	#
#																		#
#	All rights reserved by Yipeng Zhang									#
#-----------------------------------------------------------------------#
from __future__ import division

import struct
import sys
import cPickle
import math
from sklearn import svm

def euclideanDistance(instance1, instance2, length):
	distance = 0
	for x in range(length):
		distance += pow((instance1[x] - instance2[x]), 2)
	return math.sqrt(distance)



if __name__ == "__main__":
	with open('vectors.pcl', 'rb') as handle:
		vec = cPickle.load(handle)
	



