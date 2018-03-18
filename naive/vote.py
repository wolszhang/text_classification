from __future__ import division
import sys
import string
import math 

if __name__ == "__main__":
    if (len(sys.argv)<4):
        print("invalid command line argument. \n Usage: vote.py [data] [count] [vote_type]n")
        exit(0)
    out = open(sys.argv[1])
    count = open(sys.argv[2])
    vote_type = int(sys.argv[3])
    label = []
    word_count = []
    
    # count file contains two line with their word count: +1 and -1
    for line in count:
        pr = line.split()
        label.append(int(pr[0]))
        word_count.append(int(pr[1]))


    acc1 = 0
    sz1 = 0
    
    acc2 = 0
    sz2 = 0

    index = 0
    c = 0
    i = 0
    data = []
    # input format: 1 -1 0
    if (vote_type == 1):
        for line in out:
            data.append(float(line))

    # input format: count, p1, p2
    elif (vote_type==2):
        out.readline()
        for line in out:
            pr = line.split()
            data.append(float(pr[1])-float(pr[2]))

    # input format: dist
    elif (vote_type==3):
        for line in out:
            temp = math.exp(float(line))
            data.append(2*temp/(1+temp)-1)

    elif (vote_type==4):
        out.readline()
        for line in out:
            pr = line.split()
            data.append(float(pr[1])-float(pr[2]))


    acc1 = 0
    sz1 = 0
    
    acc2 = 0
    sz2 = 0

    index = 0
    c = 0
    i = 0
    for wc in word_count:
        p = 0
        m = 0
        index += wc
        while c<index:
            c+=1
            if (c>=len(data)):
                break
            p+=data[c]

        if (label[i] > 0):
            if (p>0):
                acc1+=1
            sz1+=1
        else:
            if (p<0):
                acc2+=1
            sz2+=1
        i+=1

    print("==================================================")
    if (vote_type == 1):
        print("Current Algorithm: Majority Vote (Unweighted)")
    if (vote_type == 2):
        print("Current Algorithm: Naive Bayes")
    elif (vote_type == 3):
        print("Current Algorithm: Raw Dist to Margin Majority Vote")
    elif (vote_type == 4):
        print("Current Algorithm: Weighted Logistic Regression with Dist to Margin Majority Vote")
    print("majority vote accuracy for article 1: {0}%".format(100*acc1/sz1))
    print("acc1: {0} sz1: {1}".format(acc1,sz1))
    print("majority vote accuracy for article 2: {0}%".format(100*acc2/sz2))
    print("acc2: {0} sz2: {1}".format(acc2,sz2))

    print("==================================================")
    