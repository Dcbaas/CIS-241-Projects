#include <stdio.h>
#include <ctype.h>
/**
 * lab2.c is the program for lab2 of cis 241.It's a simple echo program taking input from the 
 * user and parroting it back. While parroting, it also tracks the amount of lower and 
 * uppercase letters it has seen and displays the amount of each at the end.
 * 
 * Author: David Baas
 * Version: 1.0 - 9/7/2018
 * Since: 1.0 - 9/7/2018
 **/ 
int main(int argc, char** argv){
  char ch;
  unsigned short lowercase = 0, uppercase = 0;

  printf("Enter text (Ctrl-D to quit).\n");
  while(ch=getchar(),ch != EOF){
    //In this if statement tree, the char is checked to see if it is a
    //lowercase or uppercase letter. If it is one of those, the 
    //respective variable tracking the case is incremented up by one.
    if(islower(ch)){
      ++lowercase;
    }
    else if(isupper(ch)){
      ++uppercase;
    }
    putchar(ch);
  }

  //print the amount of lowercase and uppercase letter at the end
  printf("There were %d uppercase letters\n", uppercase);
  printf("There were %d lowercase letters\n", lowercase);

  return 0;
}

