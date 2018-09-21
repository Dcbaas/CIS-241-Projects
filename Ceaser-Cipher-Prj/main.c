#include <stdio.h>
#include <errno.h>
#include "decipher.h"

/**********************************************************************
 * The main method tracks all of the files being used and calls all
 * of the functions to deycrpt the cipher text. After decryption, 
 * The plain text is saved in the output file. 
 * 
 * Author: David Baas
 * Version: 1.0 - 9/16/2018
 * 
 * COMMAND LINE ARGUMENTS:
 * Param: {arg[1]} input_file The file contining the cipher text.
 * Param: {arg[2]} output_file The file where the plain text is going 
 * to be written to.
 * 
 * Returns: 0 on successful run, EIO on issues with either reading
 * the input file or writing the output file, EPERM if the number of 
 * arguments is not exactly 3
 *********************************************************************/
int main(int argc, char** argv){
    if(argc != 3){
        fprintf(stderr, "INVALID NUMBER OF PARAMETERS\n");
        fprintf(stderr, "USAGE: ./a.out input_file output_file\n");
        return EPERM;
    }

    FILE* frequency_values = fopen("letFreq.txt", "r");
    FILE* cipher_text = fopen(argv[1], "r");
    FILE* output_file;
    if(frequency_values == NULL){
        fprintf(stderr, "ERROR LOADING FREQUENCY VALUES\n\n");
        return EIO;
    }
    else if(!cipher_text){
        fprintf(stderr, "ERROR LOADING CIPHER TEXT\n\n");
        return EIO;
    }

    float default_freq[NUM_LETTERS];
    float observed_freq[NUM_LETTERS];
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
