#include <iostream>
#include <sstream> 
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;

int main( int argc, char *argv[] )
{
    if (argc!= 3){
        cout<<"invalid number of command line arguments"<<endl;
        cout<<"usage: vote [count] [output]"<<endl;
        return 0;
    }

    ifstream input;
    ifstream input2;
    input.open(argv[1]);
    input2.open(argv[2]);
    int flag = 0;
    vector<int> count;
    vector<int> label;
    vector<double> temp;
    string str,line;
    int a = 0, b = 0, c =0, index = 0;
    int idx_m = 0;
    int sum =  0, t = 0, f = 0;
    while(getline(input,line)){
        size_t pos = line.find(' ');
        str = line.substr(0,pos);
        line = line.substr(pos+1);
        
        count.push_back(atoi(str.c_str()));
        label.push_back(atoi(line.c_str()));
        sum +=atoi(str.c_str());
    }
    while (getline(input2,line)){
        if (count[index] == 0){
            index++;
        }
        flag = atoi(line.c_str());
        if (flag==1){
            a = a+1;
        }
        else{
            b = b+1;
        }
        c=c+1;
        if (c==count[index]){
            index++;
            idx_m++;
            if (idx_m == 3){
                idx_m = 0;
                if (a>b && label[index]==1){
                    t++;
                }
                else if (a<b && label[index]!=1){
                    t++;
                }
            }
            a = 0;
            b = 0;
            c = 0;
        }
    }
    cout<<sum<<endl;
    
    cout<<t<<endl;
    cout<<index<<endl;
    input.close();
    input2.close();

    return 0;
}