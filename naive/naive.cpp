 #include <iostream>
#include <sstream> 
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <math.h>
using namespace std;

int parse(string input , map<string, int> &word_count){
    int c = 0;
    map<string,int>::iterator itr;
    string temp, word;
    temp = input;
    size_t pos = 0;
    while (pos !=std::string::npos){
        pos = temp.find(' ');
        if (pos!=string::npos){
            word = temp.substr(0,pos);
            temp = temp.substr(pos+1);
        }
        else{
            word = temp;
        }
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
    }
    return c;
}

int compute(string output, ifstream& test_file, map<string, int> word_count1, map<string, int> word_count2, int w1, int w2, signed int type, string count){
    float rr1 = 0, rr2 = 0;
    int c1 = 0, c2 = 0, a = 0, pos = 0, c = 0;
    ofstream output_file, count_file;
    string temp, word, line;
    map<string, int>::iterator itr1, itr2;

    output_file.open(output, std::ios::out|std::ios::app);
    count_file.open(count, std::ios::out|std::ios::app);
    if (test_file.is_open()){
        while(getline(test_file,line)){
            if (line.length()<2){
                continue;
            }
            else{
                temp = line;
                pos = 0;
                c = 0;
                while (pos !=std::string::npos){
                    pos = temp.find(' ');
                    if (pos!=string::npos){
                        word = temp.substr(0,pos);
                        temp = temp.substr(pos+1);
                    }
                    else{
                        word = temp;
                    }
                    if (word.length()!=0){
                        output_file<<word;
                        itr1 = word_count1.find(word);
                        itr2 = word_count2.find(word);
                        if (itr1 != word_count1.end()){
                            rr1 =(1+(float)itr1->second)/(word_count1.size()+(float)w1)*(float)w1/(w1+w2);
                        }
                        else{
                            rr1 = 1/(word_count1.size()+(float)w1)*(float)w1/(w1+w2);
                        }
                        output_file<<" "<<log(rr1);
                        if (itr2 != word_count2.end()){
                            rr2 = (1+(float)itr2->second)/(word_count2.size()+(float)w2)*(float)w2/(w1+w2);
                        }
                        else{
                            rr2 = 1/(word_count2.size()+(float)w2)*(float)w2/(w1+w2);
                        }
                        output_file<<" "<<log(rr2)<<endl;
                        c = c+1;
                    }
                }
                count_file<<type<<" "<<c<<endl;
            }
        }
    }
    count_file.close();
    output_file.close();
    return 1;
}

int main( int argc, char *argv[] )
{
    if (argc < 7){
        cout<<"invalid number of command line arguments"<<endl;
        cout<<"usage: naive [input1] [input2] [test] [test2] [data_file] [count_file]"<<endl;
        return 0;
    }
    ifstream input_file1, input_file2, test_file1, test_file2;
    string line;
    int i = 0, w1 = 0, w2 = 0;
    size_t pos = 0; 
    double epsilon = 1;
    vector<string> input1;
    vector<string> input2;
    map<string, int> word_count1, word_count2;
   
    input_file1.open (argv[1]);
    input_file2.open (argv[2]);
    test_file1.open (argv[3]);
    test_file2.open (argv[4]);
    
    if (input_file1.is_open()){
        while(getline(input_file1,line)){
            if (line.length()<=1){
                continue;
            }
            else{
                input1.push_back(line);
            }
        }
    }
    for (unsigned int i=0;i<input1.size();i++){
        w1 = w1+parse(input1[i],word_count1);
    }
    input_file1.close();
       if (input_file2.is_open()){
        while(getline(input_file2,line)){
            if (line.length()<=1){
                continue;
            }
            else{
                input2.push_back(line);
            }
        }
    }
    for (unsigned int i=0;i<input2.size();i++){
        w2 = w2+parse(input2[i],word_count2);
    }
    input_file2.close();
    cout<<argv[5]<<endl;

    cout<<argv[6]<<endl;
    compute(argv[5],test_file1,word_count1,word_count2,w1,w2,1, argv[6]);
    compute(argv[5],test_file2,word_count1,word_count2,w1,w2,-1,argv[6]);
    return 0;
}