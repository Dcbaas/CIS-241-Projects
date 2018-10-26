#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  const int ORIGINAL = 105;
  const int SWITCH = 150;
  int mask_a = 240;
  int mask_b = 15;

  int part_a = ORIGINAL & mask_a;
  printf("%d\n", part_a);

  int part_b = ORIGINAL & mask_b;
  printf("%d\n", part_b);

  part_a = part_a >> 4;
  part_b = part_b << 4;
  int final = part_a|part_b;

  if(final == SWITCH){
    printf("Success. %d\n", final);
  }
  else{
    printf("Fail %d\n", final);
  }

  return 0;
}
