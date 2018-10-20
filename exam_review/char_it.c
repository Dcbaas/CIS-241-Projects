#include <stdio.h>
#include <string.h>


int main(){
  char* s = "Hello";

  if(strlen(s) < 7){
    for(char* it = s; *it != '\0'; it++)
      printf("%c \n", *it);
  }
}
