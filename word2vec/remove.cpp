#include <iostream>
#include <sstream> 
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

int parse(string input , map<string, int> &word_count){
    int c = 0;
    map<string,int>::iterator itr;
    string temp, word;
    temp = input;
    size_t pos = temp.find(' ');
    while (pos !=std::string::npos){
        word = temp.substr(0,pos+1);
        temp = temp.substr(pos+1);
        c++;
        if (word.size()!=0){
            itr = word_count.find(word);
            if (itr != word_count.end()){
                word_count[word]++;
            }
            else{
                word_count[word]=1;
            }
        }
        
        pos = temp.find(' ');
    }
    return c;
}


int main( int argc, char *argv[] )
{
    if (argc!= 5){
        cout<<"invalid number of command line arguments"<<endl;
        cout<<"usage: remove [input1] [input2] [output1] [output2]"<<endl;
        return 0;
    }
    ifstream input_file1, input_file2;
    ofstream output_file1, output_file2,  output_file3;
    string line;
    int w1 = 0, w2 = 0;
    float r1 =0, r2 = 0;
    float tol = 0.005;
    vector<string> input1;
    vector<string> input2;
    set<string> dic;
    map<string, int> word_count1, word_count2; 
    map<string, int>::iterator itr1, itr2;
    map<string, int>::iterator itr1copy, itr2copy;
    input_file1.open (argv[1]);
    input_file2.open (argv[2]);
    output_file1.open (argv[3]);
    output_file2.open (argv[4]);
    output_file3.open ("dic.txt");

    if (input_file1.is_open()){
        while(getline(input_file1,line)){
            input1.push_back(line);
        }
    }

    for (unsigned int i=0;i<input1.size();i++){
        w1 = w1+parse(input1[i],word_count1);
    }
    
    input_file1.close();
       if (input_file2.is_open()){
        while(getline(input_file2,line)){
            input2.push_back(line);
        }
    }
    for (unsigned int i=0;i<input2.size();i++){
        w2 = w2+parse(input2[i],word_count2);
    }
    input_file2.close();
    cout<<"removing stop words"<<endl;
    cout<<"words with over 1% frequency: "<<endl;
    for (itr1 = word_count1.begin();itr1!=word_count1.end();itr1++){
        r1 = float(itr1->second)/float(w1);
        itr2 = word_count2.find(itr1->first);
        if (itr2==word_count2.end()){
            continue;
        }
        else{
            r2 = float(itr2->second)/float(w2);
            if (r1>tol && r2>tol){
                cout<<(itr1->first)<<endl;
                dic.insert(itr1->first);
            }
        }
    }
    for (unsigned int i=0; i<input1.size();i++){
        string word, temp;
        temp = input1[i];
        size_t pos = temp.find(' ');
        while (pos !=std::string::npos){
            word = temp.substr(0,pos+1);
            temp = temp.substr(pos+1);
            if (dic.count(word)==0){
                output_file1<<word;
            }
            pos = temp.find(' ');
        }
        output_file1<<endl;
    }
    for (unsigned int i=0; i<input2.size();i++){
        string word, temp;
        temp = input2[i];
        size_t pos = temp.find(' ');
        while (pos !=std::string::npos){
            word = temp.substr(0,pos+1);
            temp = temp.substr(pos+1);
            if (dic.count(word)==0){
                output_file2<<word;
            }
            pos = temp.find(' ');
        }
        output_file2<<endl;
    }
    set<string>::iterator iter;
    for (iter = dic.begin(); iter != dic.end(); iter++) {
        output_file3<<*iter<<endl;
    }
    input_file1.close();
    input_file2.close();
    output_file1.close();
    output_file2.close();
    return 0;
}