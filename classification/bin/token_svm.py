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
#	python token_svm.py -emb vectors.pcl -train ../train 				#
#																		#
#-----------------------------------------------------------------------#
from __future__ import division
import argparse

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
		train_file = open(args.train, 'r')
		if not args.sentence_level:
			for line in train_file:
				label = line.split()[0]
				for word in line.split()[1:]:
					if '\n'+word in vec:
						vector_array.append(vec['\n'+word])
						label_array.append(label)
					else:
						print(word)


