#include <stdio.h>
#include <errno.h>
#include "decipher.h"

int main(int argc, char** argv){
    FILE* frequency_values = fopen("letFreq.txt", "r");
    FILE* cipher_text = fopen(argv[1], "r");
    FILE* output_file;
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
    int best_key = findKey(default_freq, observed_freq);

    output_file = fopen(argv[2], "w");
    if(!output_file){
        fprintf(stderr, "ERROR CREATING OUTPUT FILE");
        return EIO;
    }

    decrypt(best_key, cipher_text, output_file);

    fclose(cipher_text);
    fclose(output_file);
    return 0;
}
