#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  double* d;

  //allocate per instruction
  d = (double*) malloc(10* sizeof(double));

  //assign values to the array

  //index way
  d[1] = 5.0;

  //pointer way
  *(d + 2) = 7.0;

  //populate the array
  for(double* it = d; it < d + 10; ++it){
    *it = 1;
  }

  for(int i = 0; i < 10; ++i){
    printf("%f\n", d[i]);
  }

  free(d);

  return 0;
}
