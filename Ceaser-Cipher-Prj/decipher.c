#include <stdio.h>
#include <ctype.h>
#include <math.h>
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

int findKey(float given[], float found[]){
    float offset_sums[26];
    int best_offset = 0;

    for(int offset = 0; offset < NUM_LETTERS; ++offset){
        for(int index = 0; index < NUM_LETTERS; ++index){
           offset_sums[offset] += pow(found[(index + offset) % NUM_LETTERS] - given[index], 2);
        }
    }

    //Do an analysis of all the offset calculations to find the lowest square.
    //The lowest square will most likly be the key to decyrpt the cipher text.
    for(int index = 0; index < NUM_LETTERS; ++index){
        if(offset_sums[index] < offset_sums[best_offset]){
            best_offset = index;
        }
    }
    return best_offset;
}

void decrypt(int key, FILE* datafile, FILE* outfile){

}

char rotate(char ch, int num){
    char final;
    if(isupper(ch)){
        final = (ch - 'A' + (NUM_LETTERS - num)) % NUM_LETTERS + 'A';
    }
    else if(islower(ch)){
        final = (ch - 'a' + (NUM_LETTERS - num)) % NUM_LETTERS + 'a';   
    }
    else{
        final = ch;
    }
    
    return final;
}

