import sys
import string
import math 

if __name__ == "__main__":
    if (len(sys.argv)!=4):
        print("invalid command line argument. \n Usage: vote.py [data] [label] [train]\n")
        exit(0)
    data = open(sys.argv[1])
    label = open(sys.argv[2])
    train = open(sys.argv[3],"w")

    arr = []
    for line in label:
        arr.append(line.split()[0])

    i = 0

    for line in data:
        if (0<=int(arr[i])):
            train.write("1 1:"+line)
        else:
            train.write("0 1:"+line)
        
        i+=1
        if(i>len(arr)):
            break
