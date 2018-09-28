The Ceaser Cipher program takes a text file containing cipher text made with a Ceaser Cipher
and translates it automatically into plain text. The program looks at the cipher texts and 
compares it to letter frequencies of the english languae and tries to match an offset based of the freqencies of the cipher text.
Once a best offset is determined, the cipher text is translated to plain text and written to an
out file. If the cipher text contains less than 20 letters, the program isn't guarenteed to 
decipher the message properly as anything less than 20 letters is not statistically significant. 

This project also has a encryption program provided by the instructor It has the functionality to 
either encrypt or decyrpt a text provided that the offset is provided in both instances. 

There is a makefile provided with this assignment. It came with a compile command for the 
encryption program provided by the instructor as well as a few tests using the encryption 
program. I added a few more things. I added a compile command for the decipher program 
I created. I also created four test of my own. 

The first test is a test where the file is too short to decrypt properly. 
The second test is a file with the lowest number of letters possible, 20 letters
The third test has an abnormal amount of non letters and then a sentance.
This test is to check that the decryption is not affected by non letters
The final test is a long file. The file itself is a table of marvel super heros that 
I used for an assignment in CIS 263.

All of the test follow the method of enciphering the text file into an out file,
then followed by decrypting the out file into a bak file. Finally, The txt file 
and the bak file are compared using the diff command. If the files are not identical,
then the decyrption failed. 
