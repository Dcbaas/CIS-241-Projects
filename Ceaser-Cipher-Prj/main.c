#include <stdio.h>
#include <errno.h>
#include "decipher.h"

int main(int argc, char** argv){
    printf("here -1");
    FILE* frequency_values = fopen("letFreq.txt", "r");

    if(frequency_values == NULL){
        printf("ERROR LOADING FILE");
        return ENOENT;
    }
    printf("here0");
    float default_freq[26];
    readFreq(default_freq, frequency_values);


    fclose(frequency_values);
    return 1;
}