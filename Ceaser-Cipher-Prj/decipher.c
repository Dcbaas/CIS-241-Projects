#include <stdio.h>
#include <ctype.h>
#include "decipher.h"

void readFreq(float found[], FILE* letFreq){
    char throwaway_buffer[3];

    //Throws away the first two chars of the file. They are not used.
    fgetc(letFreq);
    fgetc(letFreq);

    for(int index = 0; index < NUM_LETTERS; ++index){
        printf("here2");
        fscanf(letFreq,"%f", &found[index]);
        for(int j = 0; j < 2; ++j){
            fgetc(letFreq);
        }
    }
}

void calcFreq(float found[], FILE* datafile){
    char observed;

    while(observed = fgetc(datafile), observed != EOF){
        if(isupper(observed)){
            
        }
    }    

    // char rotate(char ch, int num){

    // }

    // int findKey(float given[], float found[]){

    // }

    void decrypt(int key, FILE* datafile, FILE* outfile){

    }
