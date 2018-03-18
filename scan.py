import logging
import os.path
import six
import sys


if __name__ == '__main__':
	with open("./data/textsss") as infile:
		i=0
		for line in infile:
			print(line)
			if (i==100):
				break