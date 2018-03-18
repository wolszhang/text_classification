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
        cout<<"usage: remove [input1] [input2] [output1] [output2] "<<endl;
        return 0;
    }
    ifstream input_file1, input_file2, input_file3;
    ofstream output_file1, output_file2;
    string line;
    vector<string> input1;
    vector<string> input2;
    set<string> dic;
    map<string, int> word_count1, word_count2; 
    map<string, int>::iterator itr1, itr2;
    map<string, int>::iterator itr1copy, itr2copy;

    input_file1.open (argv[1]);
    input_file2.open (argv[2]);
    input_file3.open ("dic.txt");
    
    output_file1.open (argv[3]);
    output_file2.open (argv[4]);

    if (input_file1.is_open()){
        while(getline(input_file1,line)){
            input1.push_back(line);
            parse(line,word_count1);
        }
    }
    input_file1.close();
    if (input_file2.is_open()){
        while(getline(input_file2,line)){
            input2.push_back(line);
            parse(line,word_count2);
        }
    }
    input_file2.close();
    if (input_file3.is_open()){
        while(getline(input_file3,line)){
            dic.insert(line);
        }
    }
    input_file3.close();
    for (unsigned int i=0; i<input1.size();i++){
        string word, temp;
        temp = input1[i];
        size_t pos = temp.find(' ');
        while (pos !=std::string::npos){
            word = temp.substr(0,pos+1);
            temp = temp.substr(pos+1);
            if (dic.count(word)!=0){
            }
            else{
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
            if (dic.count(word)!=0){
            }
            else{
                output_file2<<word;
            }
            pos = temp.find(' ');
        }
        output_file2<<endl;
    }
    input_file1.close();
    input_file2.close();
    output_file1.close();
    output_file2.close();
    return 0;
}