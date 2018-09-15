#include <stdio.h>
#include <ctype.h>
#include "decipher.h"

void readFreq(float found[], FILE* letFreq){
    char throwaway_buffer[3];

    //Throws away the first two chars of the file. They are not used.
    fgetc(letFreq);
    fgetc(letFreq);

    for(int index = 0; index < NUM_LETTERS; ++index){
        fscanf(letFreq,"%f", &found[index]);
        for(int j = 0; j < 2; ++j){
            fgetc(letFreq);
        }
    }
}

void calcFreq(float found[], FILE* datafile){
    char observed;
    int letter_freq[26] = {0};    
    int index, total_letters = 0;
    while(observed = fgetc(datafile), observed != EOF){
        if(isupper(observed)){
            index = (int) observed - 'A';
            ++total_letters;
        }
        else if(islower(observed)){
            index = (int) observed - 'a';
            ++total_letters;
        }
        ++letter_freq[index];
    }    

    //Calculate the letter frequencies
    for(index = 0; index < NUM_LETTERS; ++index){
        found[index] = (float) letter_freq[index] / total_letters;
    }
}

// char rotate(char ch, int num){

// }

int findKey(float given[], float found[]){
    float offest_sums[26];
    for(int offset = 0; offset < NUM_LETTERS; ++offset){
        for(int index = 0; index < NUM_LETTERS){
            
        }
    }
}

void decrypt(int key, FILE* datafile, FILE* outfile){

}
