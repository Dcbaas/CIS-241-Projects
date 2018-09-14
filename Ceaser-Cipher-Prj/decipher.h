#ifndef DECIPHER_H
#define DECIPHER_H 
#include <stdio.h> 

void readFreq(float found[], FILE* letFreq);
void calcFreq(float found[], FILE* datafile);
char rotate(char ch, int num);
int findKey(float given[], float found[]);
void decrypt(int key, FILE* datafile, FILE* outfile);

#endif


