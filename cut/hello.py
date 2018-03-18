import sys
import gensim
from nltk.tokenize import sent_tokenize
from nltk.stem.snowball import PorterStemmer
from nltk.corpus import stopwords
import string 
from random import randint

if __name__ == "__main__":
	ran = randint(0,1)
	print(ran)