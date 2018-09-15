#include <stdio.h>
#include "decipher.h"

void readFreq(float found[], FILE* letFreq){
    printf("here1");
    char throwaway_buffer[3];
    fgetc(letFreq);
    fgetc(letFreq);
    for(int index = 0; index < NUM_LETTERS; ++index){
        printf("here2");
        fscanf(letFreq,"%f", &found[index]);
        for(int j = 0; j < 2; ++j){
            fgetc(letFreq);
        }
        printf("here3");
    }
}

void calcFreq(float found[], FILE* datafile){

}

// char rotate(char ch, int num){

// }

// int findKey(float given[], float found[]){

// }

void decrypt(int key, FILE* datafile, FILE* outfile){

}