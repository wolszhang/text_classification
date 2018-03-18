import re
import sys
import os
from random import randint

def st_depth(st):
    return st.count('_')

def st_dist(key1, key2):
    leng = min(len(key1),len(key2))
    s =0
    for i in range(0,leng):
        if (key1[i]==key2[i]):
            continue
        else:
            s = i
            break
    return st_depth(key1[s:]) + st_depth(key2[s:])+2



if __name__ == "__main__":
    inp_depth = 10
    dist = 2

    max_d = 0
    node = 0
    art_c = 0
    inp1 = open("life_tree.txt",'r')
    tree = dict()
    for line in inp1:
        par = line.rstrip('\n').split(':')
        temp = []
        index = par[0]
        for word in par[1].split(','):
            if (len(word)>0):
                temp.append(word)
        tree[index] = temp
        if (st_depth(index) > max_d):
            max_d = st_depth(index)
        node += 1
        art_c += len(temp)
    print("tree with "+str(node) + " nodes " + str(art_c) + " articles and "+ str(max_d) + " height reconstructed")
    
    sample_size = 100
    sample = []

    avail = dict()
    for key, value in tree.items():
        if st_depth(key) in avail:
            avail[st_depth(key)].append(key)
        else:
            avail[st_depth(key)]= [key]
    for i in avail:
        print("level "+str(i) + " has "+str(len(avail[i])))
        

    while inp_depth < 20:
        dist = 2
        while dist < 20:        
            print(inp_depth)
            print(dist)
            cnt = 0
            sample = []
            for key1 in avail[int(inp_depth)]:
                for key2 in avail[int(inp_depth)]:
                    if st_dist(key1, key2) == int(dist) and not key1 == key2:
                        sample.append((key1,key2))
            
            while cnt < 0.1 * len(sample) :
                cnt += 1
                ran = cnt*10 + randint(0,10) - 10
                if ran >= len(sample):
                    break
                (key1, key2) = sample[ran]
                
                lst1 = []
                lst2 = []

                for key, value in tree.items():
                    if key.startswith(key1):
                        for ar in value:
                            lst1.append(ar)
                    if key.startswith(key2):
                        for ar in value:
                            lst2.append(ar)

                temp = ""
                directory = "./output/level"+str(inp_depth) + "dist" + str(dist)+ "/"+str(cnt)+"/"
                if not os.path.exists(directory):
                    os.makedirs(directory)
                for item in lst1:
                    if os.path.exists("file/"+str(item.strip())+".txt"):
                        inp = open("file/"+str(item.strip())+".txt", 'r').read()
                        temp+=inp
                outp = open(directory + "1.txt",'w')
                outp.write(temp)

                temp = ""
                for item in lst2:
                    if os.path.exists("file/"+str(item.strip())+".txt"):
                        inp = open("file/"+str(item.strip())+".txt", 'r').read()
                        temp+=inp
                outp = open(directory + "2.txt",'w')
                outp.write(temp)
            print(str(cnt) + " pairs of artcles generated")
            dist = dist + 2
        inp_depth += 1