#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "queue.h"
#include "data_struct.h"

int load_data(ArrivalData* data);
void simulation(int numTellers);
double expdist(double mean);

int main(int argc, char** argv){
  ArrivalData* arrival_data = (ArrivalData*) malloc(sizeof(ArrivalData));
  load_data(arrival_data);

  free(arrival_data);
  return 0;
}

int load_data(ArrivalData* data){
  FILE* input_file = fopen("proj2.dat", "r");

  if(!input_file){
    fprintf(stderr, "ERROR: FAILURE TO LOAD DAT FILE");
    fclose(input_file);
    return EIO;
  }

  for(int index = 0; index < TABLE_SIZE; ++index){
    fscanf(input_file, "%i %i", 
        &(data->customers_per_min[index]), 
        &(data->percent_data[index]));
    printf("%d %d\n",data->customers_per_min[index], data->percent_data[index]);
  }

  fclose(input_file);
  return 0;
}


