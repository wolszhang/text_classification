#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h> // mac os x

const long long max_size = 200;          // max length of strings

int main(int argc, char **argv){
	char input_file[max_size], input_file2[max_size], output_file[max_size],c_file[max_size];
	if (argc != 4 && argc != 5 ){
		printf("Usage: ./cb <INPUT> <INPUT2> <OUTPUT> \nwhere FILE contains word projections in the BINARY FORMAT\n");
    	return 0;
	}
	strcpy(input_file, argv[1]);
	strcpy(input_file2, argv[2]);
	strcpy(output_file, argv[3]);
    strcpy(c_file, argv[4]);
	int train1 = 0;
	int train2 = 0;
  	FILE *input, *input2, *output, *count_file;
	input = fopen(input_file, "rb");
	input2 = fopen(input_file2, "rb");
	
    output = fopen(output_file,"w++");
    count_file = fopen(c_file,"w++");
    char* buffer;
	size_t leng;
  	while(getline(&buffer, &leng, input) != -1){
        train1++;
        fprintf(output, "%s",buffer);
    }
    while(getline(&buffer, &leng, input2) != -1){
        train2++;
        fprintf(output, "%s",buffer);
    }

    if (argc == 5){

        FILE *wc, *wc2, *output2;
        wc = fopen("1","rb");
        wc2 = fopen("-1","rb");
    
        while(getline(&buffer, &leng, wc) != -1){
            fprintf(count_file, "1 %s", buffer);
        } 
        while(getline(&buffer, &leng, wc2) != -1){
            fprintf(count_file, "-1 %s", buffer);
        } 
        fclose(wc);
        fclose(wc2);
        fclose(output2);

    }
    fclose(input);
    fclose(input2);
    fclose(output);
    printf("train data 1: %d\ntrain data 2: %d\n",train1, train2);
    return 0;
}