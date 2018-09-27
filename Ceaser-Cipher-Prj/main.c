#include <stdio.h>
#include <errno.h>
#include "decipher.h"

/**********************************************************************
 * The main method tracks all of the files being used and calls all
 * of the functions to deycrpt the cipher text. After decryption, 
 * The plain text is saved in the output file. For all data structures
 * used in this assignment I used static arrays. This decsion was 
 * taken because All the arrays used all needed only 26 elements 
 * and in every use case the entire array was filled. With that in 
 * mind, it was more pruident to use the safer static array rather
 * than deal with possible memory problems of dynamic arrays.
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
    //Validate the number of arguments.
    if(argc != 3){
        fprintf(stderr, "INVALID NUMBER OF PARAMETERS\n");
        fprintf(stderr, "USAGE: ./a.out input_file output_file\n");
        return EPERM;
    }

    //Define all the files and open two of them.
    FILE* frequency_values = fopen("letFreq.txt", "r");
    FILE* cipher_text = fopen(argv[1], "r");
    FILE* output_file;

    //Check that both frequency and cipher text opened correctly.
    if(frequency_values == NULL){
        fprintf(stderr, "ERROR LOADING FREQUENCY VALUES\n\n");
        return EIO;
    }
    else if(!cipher_text){
        fprintf(stderr, "ERROR LOADING CIPHER TEXT\n\n");
        return EIO;
    }

    //Define two arrays for given and observed letter frequencies.
    float default_freq[NUM_LETTERS];
    float observed_freq[NUM_LETTERS];

    //Read in the given frequencies and close the frequency file.
    readFreq(default_freq, frequency_values);
    fclose(frequency_values);

    //Calculate the frequency for the cipher text and find the best
    //offset.
    calcFreq(observed_freq, cipher_text);
    int best_key = findKey(default_freq, observed_freq);

    //Open the output file now and validate it was opened correctly.
    //I do this later from the others because my perceiption is that
    //the less time I have a file open the better. File I/O is 
    //very tempermental I think.
    output_file = fopen(argv[2], "w");
    if(!output_file){
        fprintf(stderr, "ERROR CREATING OUTPUT FILE");
        return EIO;
    }

    //Decrypt the cipher text and write it to the output file.
    decrypt(best_key, cipher_text, output_file);

    //Close all of the remaining open files.
    fclose(cipher_text);
    fclose(output_file);

    //Success.
    return 0;
}
