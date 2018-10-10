#ifndef DECIPHER_H
#define DECIPHER_H 
#include <stdio.h>

#define NUM_LETTERS 26

/**********************************************************************
 * decipher.h defines the series of functions to decipher a text file
 * with cipher text.
 * 
 * Author: David Baas
 * Version: 1.0 - 9/16/2810
 *********************************************************************/

/**********************************************************************
 * Takes the specified file and reads out all of the frequency values
 * of the normal alphabet. It then takes those values and copies them
 * into the found array. The file is expected to be the file with 
 * the name letFreq.txt. Any other file will not produce valid results.
 * 
 * Param: found A float array that will store the frequency values.
 * Param: letFreq The file where the frequency values will be extracted.
 *********************************************************************/
void readFreq(float found[], FILE* letFreq);

/**********************************************************************
 * Takes the specified input file and generates frequency statistics 
 * regarding the cipher text. The resulting frequency analysis is 
 * stored in the found array. 
 * 
 * Param: found A float array used to analyze the character frequency.
 * Param: datafile: The file with the cipher text being deciphered.
 *********************************************************************/
void calcFreq(float found[], FILE* datafile);

/**********************************************************************
 * Rotate the character in parameter ch down the alphabet for the
 * number of positions as given in parameter num and return the 
 * resulting character.
 * 
 * Param: ch The character being changed.
 * Param: num the number of places it is being rotated.
 * Returns: A char converted from a base char and a number modifier.
 *********************************************************************/
char rotate(char ch, int num);

/**********************************************************************
 * Analyzes the frequency values of the cipher text and compares it
 * against the cipher text. The resulting key will be determined 
 * by how close an offset matches the given frequencies. 
 * 
 * Param: given The array of letter frequency in plain text.
 * Param: found The array of letter frequency in the cipher text.
 * Return: The best offset key match for the associated cipher text.
 *********************************************************************/
int findKey(float given[], float found[]);

/**********************************************************************
 * Takes the cipher text in the file and converts it to plain text. 
 * It is important that the either the datafile has been closed and 
 * reopened again or is starting from the beginning of the original
 * file used in calcFrequency otherwise the decryption won't happen.
 * All non-letter characters are preserved. this means any spaces or
 * numbers used remain the same. 
 * 
 * Param: key The offset used to decipher the cipher text
 * Param: datafile The text file containing the cipher text.
 * Param: outfile The text file that will have the plain text written
 * to it.
 *********************************************************************/
void decrypt(int key, FILE* datafile, FILE* outfile);

#endif
