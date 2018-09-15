#include <stdio.h>
#include <errno.h>
#include "decipher.h"

int main(int argc, char** argv){
    printf("here -1");
    FILE* frequency_values = fopen("letFreq.txt", "r");
    FILE* cipher_text = fopen(argv[1], "r");

    if(frequency_values == NULL){
        fprintf(stderr, "ERROR LOADING FREQUENCY VALUES\n\n");
        return ENOENT;
    }
    else if(!cipher_text){
        fprintf(stderr, "ERROR LOADING CIPHER TEXT\n\n");
        return ENOENT;
    }

    float default_freq[26];
    float observed_freq[26];
    readFreq(default_freq, frequency_values);
    fclose(frequency_values);

    calcFreq(observed_freq, cipher_text);
    fclose(cipher_text);

    
    return 0;
}
