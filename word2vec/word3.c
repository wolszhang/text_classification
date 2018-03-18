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
  FILE *input, *output, *out2;
  char* word;
  char* buffer;
  int c = 0, i = 0, sc = 0, p = 0;
  long long b = 0;
  size_t leng;
  if (argc < 4) {
    printf("Usage: ./sentence2vec <FILE> <INPUT> <OUTPUT> <OUTPUT2> <FLAG> \nwhere FILE contains word projections in the BINARY FORMAT\n");
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
  out2 = fopen(argv[4],"w++");
  fprintf(out2,"hello");
    
    printf("%d\n",sc);
    printf("%d\n",p);
    fclose(input);
    fclose(output);
    fclose(f);
    free(M);
    free(vocab);
    
    return 0;
}
