//  Copyright 2013 Google Inc. All Rights Reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h> // mac os x

const long long max_size = 2000;          // max length of strings
const long long max_w = 50;              // max length of vocabulary entries
const int mode = 1;
// a mode of 0 convert each word
// a mode of 1 convert the whole sentence

int small(char* buffer, int size){
  int a;
  for (a=0; a<size; a++){
    if (buffer[a]=='.'){
    buffer[a] = '\0';
    return 0;
    }
    if (buffer[a]=='\n'){
        buffer[a] = '\0';
    }
    if (buffer[a]=='!' || buffer[a]=='"'){
        buffer[a] = ' ';
    }
  }
  return 0;
}


int main(int argc, char **argv) {
  FILE *f;
  char input_file[max_size], dic[max_size], output_file[max_size];
  float len;
  long long words, size, a;
  char ch;
  float *M;
  char *vocab;
  FILE *input, *output, *output2;
  char* word;
  char* buffer;
  int c = 0, i = 0, sc = 0, p = 0;
  long long b = 0;
  float *s;
  float *t;
  size_t leng;
  if (argc < 4) {
    printf("Usage: ./sentence2vec <FILE> <INPUT> <INPUT2> <OUTPUT> \nwhere FILE contains word projections in the BINARY FORMAT\n");
    return 0;
  }
  strcpy(dic, argv[1]);
  strcpy(input_file, argv[2]);
  strcpy(output_file, argv[3]);
  int flag = atoi(argv[4]);
  f = fopen(dic, "rb");

  if (f == NULL ) {
    printf("vector input file not found\n");
    return -1;
  }
  fscanf(f, "%lld", &words);
  fscanf(f, "%lld", &size);
    
    
  input = fopen(input_file, "rb");
  output = fopen(output_file,"w++");
  output2 = fopen("count.txt","w++");
  printf("input : %s\noutput : %s\n",input_file,output_file);
  s = (float *)calloc(size, sizeof(float)); //sum
  t = (float *)calloc(size, sizeof(float)); //max
  if (input == NULL || output == NULL) {
      printf("Input file not found\n");
      return -1;
  }
    
  vocab = (char *)malloc((long long)words * max_w * sizeof(char));
  M = (float *)malloc((long long)words * (long long)size * sizeof(float));
  if (M == NULL) {
    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
    return -1;
  }
  printf("words :%lld\nsize: %lld\n",words,size);
  for (b = 0; b < words; b++) {
    fscanf(f, "%s%c", &vocab[b * max_w], &ch);
    for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
    len = 0;
    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
    len = sqrt(len);
    for (a = 0; a < size; a++) M[a + b * size] /= len;
  }
  while(getline(&buffer, &leng, input) != -1){
        //printf("%d\n",p);
        sc++;
        c = 0;
        small(buffer, strlen(buffer));
        
        if (strlen(buffer)==0) continue;
        if (mode == 1){
            //sentence to vector
            word = strtok (buffer," ,.-\n");
            while (word != NULL){
                for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], word)) break;
                if (b == words) {
                    b = -1;
                    word = strtok (NULL, " ,.-");
                    continue;
                }
                else{
                    c++;
                    for (i=0 ;i<size; i++){
                        s[i] += M[i+b*size];
                    }
                    for (i=0 ;i<size; i++){
                        if (M[i+b*size]>t[i]){
                            t[i] = M[i+b*size];
                        }
                    }
                }
                word = strtok (NULL, " ,.-");
            }
            if (c > 0){
                fprintf(output,"%d ",flag);
                for (i=0 ;i<size; i++){
                    fprintf(output, "%d:%f ",i+1,s[i]);
                    s[i] = 0;
                }
                fprintf(output, "\n");
                p++;
            }
        }
        if (mode == 0){
            //word to vector
            word = strtok (buffer," ,.-\n");
            while (word != NULL){
                for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], word)) break;
                if (b == words) {
                    b = -1;
                    //printf("not found: %s\n",word);
                    word = strtok (NULL, " ,.-");
                    continue;
                }
                else{
                    fprintf(output,"+1 ");
                    for (i=0 ;i<size; i++){
                        fprintf(output, "%d:%f" ,i+1,M[i+b*size]);
                        if (i!=size-1){
                            fprintf(output, " ");
                        }
                    }
                    fprintf(output, "\n");
                    p++;
                }
                word = strtok (NULL, " ,.-");
                //printf("%s\n",word);
            }
        }
        fprintf(output2,"%d +1\n",p);
        p = 0;
    }
    printf("%d\n",sc);
    printf("%d\n",p);
    fclose(input);
    fclose(output);
    
    free(s);
    free(t);
    
    fclose(f);
    free(M);
    free(vocab);
    
    return 0;
}
