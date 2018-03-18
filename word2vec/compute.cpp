#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

// This function group sentence_count number of lines together and scan through words by reducing them and remove other characters
// put together three sentences
int sentence_count;

void filter(string& word){
    for (unsigned int i=0;i<word.size();i++){
        if (word[i]<='Z'&&word[i]>='A'){
            word[i] = word[i]-'A'+'a';
        }
        else if (word[i]<'A'){
            word = word.substr(0,i);
        }
    }
}


int main( int argc, char *argv[] )
{
    if (argc != 3 && argc!= 4){
        cout<<"invalid number of command line arguments"<<endl;
        cout<<"usage: compute [input] [output] [optional sentence_count]"<<endl;
        return 0;
    }
    if (argc == 4){
        sentence_count = atoi(argv[3]);
    }
    else{
        sentence_count = 1;
    }
    
    int count = 0;
    ifstream input_file;
    ofstream output_file;
    string line, buffer, text, word;
    wstring word2;
    vector<string> input;
    input_file.open (argv[1]);
    buffer = "";
    cout<<"Filter text input "<<argv[1]<<endl;
    
    output_file.open (argv[2]);
    if (input_file.is_open()){
        while(getline(input_file,line)){
            buffer.append(line);
            count++;
            if (count==sentence_count){
                size_t w_pos = buffer.find(' ');

                while (w_pos !=std::string::npos){
                    if (w_pos<=1){
                        buffer = buffer.substr(w_pos+1);
                        w_pos = buffer.find(' ');
                    }
                    else{
                        word = buffer.substr(0,w_pos+1);
                        buffer = buffer.substr(w_pos+1);
                        filter(word);
                        output_file<<word + " ";
                        w_pos = buffer.find(' ');
                    }
                }
                if (count != 0){
                    output_file<<'\n';
                }
                buffer = "";
                count = 0;
           }
        }
    }
    output_file.close();
    input_file.close();
    return 0;
}