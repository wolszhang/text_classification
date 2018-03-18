#include <iostream>
#include <sstream> 
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

double split(string temp, int& digit){
    size_t pos = temp.find(':');
    digit = atoi(temp.substr(0,pos-1).c_str());
    double d = atof(temp.substr(pos+1).c_str());
    return d;
}

int NN(vector<vector<double> >data, vector<int> label, vector<double> m, int kn){
    bool flag = true;
    int* NN = (int*)calloc(kn, sizeof(int));
    double dist = 1000, sum = 0;
    int idx = 0;
    int label_1 = 0, label_0 = 0;
    for (int i= 0; i<kn;i++){
        cout<<"iteration "<<i<<endl<<endl<<endl;
        for (int j=0;j<data.size();j++){
            sum = 0;
            flag = true;
            for (int k=0; k<data[j].size();k++){
                sum = sum + (data[j][k] - m[k])*(data[j][k] - m[k]);
            }
            if (sum < 0.0001){
                cout<<"machine epsilon"<<endl;
                flag = false;
            }
            for (int x = 0; x < i; x++){
                if (j==NN[x]){
                    cout<<"appear in "<<x<<endl;
                    flag = false;
                }
            }
            cout<<" itr "<<j<<" dist:"<<dist<<" sum:"<<sum<<" flag: "<<flag<<endl;
            if (flag == false){
                sum = dist+1;
            }
            if (dist > sum){
                dist = sum;
                idx = j;
            }   
        }
        NN[i] = idx;
        cout<<"setting NN "<<i<<" to be "<<idx<<endl;
        idx = 0;
        sum = 0;
        dist = 1000;
        cout<<NN[i]<<endl;
    }
    for (int i=0;i<kn;i++){
        if (label[NN[i]] == 1){
            label_1 ++;
        }
        else{
            label_0 ++;
        }
    }
    cout<<"neighbors: "<<endl;
    cout<<"1:"<<NN[0]<<" / "<<label[NN[1]]<<endl;
    cout<<"2:"<<NN[1]<<" / "<<label[NN[2]]<<endl;
    cout<<"3:"<<NN[2]<<" / "<<label[NN[3]]<<endl;
    cout<<endl;
    cout<<endl;
    free(NN);
    if (label_1 > label_0){
        return 1;
    }
    return -1;
}

int close(vector<vector<double> >data,vector<int> label, int i,int c_label){
    double sum, dist;
    int idx = 0;
    for (int j=0;j<label.size();j++){
        if (i==j){
            continue;
        }
        if (label[j]!=c_label){
            continue;
        }
        for (int k=0; k<data[j].size();k++){
            sum = sum + (data[j][k] - data[j][i])*(data[j][k] - data[j][i]);
        }
        if (dist == 0 && idx == 0){
            dist = sum;
            idx = j;
            sum = 0;
        }
        else if (dist > sum){
            dist = sum;
            idx = j;
            sum = 0;
        }
    }
    return idx;
}

void print(vector<vector<double> > data){
    cout<<"data:"<<endl;
    for (int i=0;i<data.size();i++){
        for (int j=0;j<data[i].size();j++){
            cout<<setw(3)<<data[i][j];
        }
        cout<<endl;
    }
}
int main( int argc, char *argv[] )
{
    if (argc!= 4){
        cout<<"invalid number of command line arguments"<<endl;
        cout<<"usage: condense [input] [output] [k]"<<endl;
        return 0;
    }

    ifstream input;
    ofstream output;
    input.open(argv[1]);
    output.open(argv[2]);
    int k = atoi(argv[3]);
    int count;
    vector<vector<double> >data;
    vector<signed int> label;
    vector<double> temp;
    vector<vector<double> > set;
    vector<signed int> set_label;
    double res;
    string str,line;
    bool flag = true;
    int itr = 0;
    int a = 0, b = 0, c =0;
    while(getline(input,line)){
        temp.clear();
        if (line[0] =='+'){
            label.push_back(1);
        }
        else{
            label.push_back(-1);
        }
        size_t pos = line.find(' ');
        line = line.substr(pos+1);
        pos = line.find(' ');
        while (pos!=std::string::npos){
            str = line.substr(0,pos);
            res = split(str,c);
            temp.push_back(res);
            line = line.substr(pos+1);
            pos = line.find(' ');
        }
        temp.push_back(split(line,c));
        data.push_back(temp);
    }
    set.push_back(data[1]);
    set_label.push_back(label[1]);
    set.push_back(data[2]);
    set_label.push_back(label[2]);
    set.push_back(data[3]);
    set_label.push_back(label[3]);
    
    while (flag && itr<10){
        cout<<itr<<endl;
        flag = false;
        for (int i=0; i<1;i++){
            for(int z = 0; z<data[i].size();z++){
                cout<<data[i][z];
            }
            cout<<endl;
            c = NN(data,label,data[i],k);
            b = NN(set,set_label,data[i],k);
            cout<<"i"<<i<<" "<<b<<" / "<<c<<" label:"<<label[i]<<endl;
            if (b!= c){
                cout<<"caught one"<<endl;
                flag = true;
                a = close(data,label,i,c);
                set.push_back(data[a]);
                set_label.push_back(label[a]);
            }
        }
        itr++;
    }
    cout<<flag;
    cout<<itr<<endl;
    cout<<set.size()<<endl;
    print(data);
    /*
    for (int i=0;i<set.size();i++){
        output<<set_label[i];
        for (int j=0; j<set[i].size();j++){
            output<<set[i][j]<<endl;
        }
    }
    */
    
    
    return 0;
}