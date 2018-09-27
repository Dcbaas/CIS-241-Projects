#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "decipher.h"

/**********************************************************************
 * decipher.c implements the functions defined in decipher.h
 * 
 * Authoer: David Baas
 * Version: 1.0 - 9/16/2810
 *********************************************************************/

/**********************************************************************
 * Takes the spcified file and reads out all of the frequency values
 * of the normal alphebet. It then takes those values and copies them
 * into the found array. The file is expected to be the file with 
 * the name letFreq.txt. Any other file will not produce valid results.
 * 
 * Param: found A float array that will store the frequency values.
 * Param: letFreq The file where the frequency values will be extracted.
 *********************************************************************/
void readFreq(float found[], FILE* letFreq){
    char throwaway_buffer[3];

    //Throws away the first two chars of the file. They are not used.
    fgetc(letFreq);
    fgetc(letFreq);

    //read all of the values and throw away the letters for each line.
    for(int index = 0; index < NUM_LETTERS; ++index){
        fscanf(letFreq,"%f", &found[index]);
        for(int j = 0; j < 2; ++j){
            fgetc(letFreq);
        }
    }
}

/**********************************************************************
 * Takes the specified input file and genrates frequency statistics 
 * regarding the ciper text. The resulting frequency anaylisis is 
 * stored in the found array. 
 * 
 * Param: found A float array used to analyze the character frequency.
 * Param: datafile: The file with the cipher text being deciphered.
 *********************************************************************/
void calcFreq(float found[], FILE* datafile){
    //A value to observe each char in the txt file.
    char observed;

    //An integer array to track letter frequencies. 
    //The found[] array isn't used for this function because floating points might become inaccurate 
    int letter_freq[26] = {0};    
    int index, total_letters = 0;

    //Parse the file for letters and increase their frequency if found.
    while(observed = fgetc(datafile), observed != EOF){
        if(isupper(observed)){
            index = (int) observed - 'A';
            ++total_letters;
            ++letter_freq[index];
        }
        else if(islower(observed)){
            index = (int) observed - 'a';
            ++total_letters;
            ++letter_freq[index];
        }
    }    

    //Calculate the letter frequencies
    for(index = 0; index < NUM_LETTERS; ++index){
        found[index] = (float) letter_freq[index] / total_letters;
    }
}

/**********************************************************************
 * Analyzes the frequency values of the cipher text and compares it
 * against the cipher text. The resulting key will be determined 
 * by how close an offset matches the given frequencies. 
 * 
 * Param: given The array of letter frequency in plain text.
 * Param: found The array of letter frequency in the cipher text.
 * Return: The best offset key match for the associated cipher text.
 *********************************************************************/
int findKey(float given[], float found[]){
    float offset_sums[26];
    int best_offset = 0;

    //Calcuating all of the offsets.
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

/**********************************************************************
 * Takes the cipher text in the file and converts it to plain text. 
 * It is important that the either the datafile has been closed and 
 * reopened again or is starting from the beginning of the origianl
 * file used in calcFrequency otherwise the decryption won't happen.
 * All non letter characters are preserved. this means any spaces or
 * numbers used remain the same. 
 * 
 * Param: key The offset used to deciper the cipher text
 * Param: datafile The text file containing the cipher text.
 * Param: outfile The text file that will have the plain text written
 * to it.
 *********************************************************************/
void decrypt(int key, FILE* datafile, FILE* outfile){
    rewind(datafile); 
    char ch;

    while(ch = fgetc(datafile), ch != EOF){
        fputc(rotate(ch, key), outfile); 
    }
}

/**********************************************************************
 * Rotate the character in parameter ch down the alphabet for the
 * number of positions as given in parameter num and return the 
 * resulting character.
 * 
 * Param: ch The character being changed.
 * Param: num the number of places it is being rotated.
 * Returns: A char converted from a base char and a number modifier.
 *********************************************************************/
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

