from __future__ import division
import sys
import string 

if __name__ == "__main__":
    if (len(sys.argv)!=3):
        print("invalid command line argument. \n Usage: vote.py [input1] [count]\n")
        exit(0)
    inp = open(sys.argv[1])
    count = int(sys.argv[2])



    word_count = []
    for line in inp:
        word_count.append(int(line))
    
    acc1 = 0
    sz1 = 0
    acc2 = 0
    sz2 = 0
    c = 0
    for wc in word_count:
        c+=1
        if (c<count):
            if (wc == 1):
                acc1 +=1
            sz1 +=1
        else:
            if (wc != 1):
                acc2 +=1
            sz2 +=1
    print("total sentences: ",c)
    print("sen2vec accuracy for article 1: {0}%".format(100*acc1/sz1))
    print("sen2vec accuracy for article 2: {0}%".format(100*acc2/sz2))