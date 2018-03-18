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

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(){
    ofstream output_file1;
    ofstream output_file2;
    output_file1.open("train.txt");
 	output_file2.open("test.txt");
 	for (int i=0;i<50;i++){
 		output_file1<<"1 ";
 		for (int j=0;j<10;j++){
 			output_file1<<j+1<<":"<<fRand(0,1)<<" ";
 		}
 		output_file1<<endl;
 	}
 	for (int i=0;i<50;i++){
 		output_file1<<"0 ";
 		for (int j=0;j<10;j++){
 			output_file1<<j+1<<":"<<fRand(0,1)<<" ";
 		}
 		output_file1<<endl;
 	}
 	for (int i=0;i<10;i++){
 		output_file2<<"1 ";
 		for (int j=0;j<10;j++){
 			output_file2<<j+1<<":"<<fRand(0,1)<<" ";
 		}
 		output_file2<<endl;
 	}
 	for (int i=0;i<10;i++){
 		output_file2<<"0 ";
 		for (int j=0;j<10;j++){
 			output_file2<<j+1<<":"<<fRand(0,1)<<" ";
 		}
 		output_file2<<endl;
 	}
     
      output_file1.close();  
      output_file2.close();
}