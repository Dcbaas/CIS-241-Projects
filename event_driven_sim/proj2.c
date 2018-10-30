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

/***********************************************************************
 * Loads the data for the arrival time of customers. This will be used
 * in the simulation to simulate customer arrival times. 
 *
 * Param: data a pointer to the ArrivalData struct the data will be 
 * loaded into. 
 * Return: 0 if all was successful, EIO if there was a problem loading
 * the file.
 **********************************************************************/
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


/**********************************************************************
 * Simulates the amount of time it takes to serve one customer at the 
 * counter. The result of this will be stored in a teller array slot 
 * to signify that the teller is busy.
 *
 * Param mean The avg time it takes to serve on customer.
 * Return a random duration it will take to serve a customer. 
 **********************************************************************/
double expdist(double mean){
  double random_num = rand();
  random_num /= RAND_MAX;
  return -mean * log(random_num);
}

