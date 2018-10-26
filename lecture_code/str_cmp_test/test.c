#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
  char* str1 = "day";
  char* str2 = "day";
  char str3[4];
  char* str4 = "day9";

  strcpy(str3, str1);
  int comparison = strcmp(str1, str4);

  printf("%s\n", str1);
  printf("%s\n", str2);
  printf("%s\n", str3);
  printf("%d\n", comparison);

  return 0;
}
