#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "queue.h"
#include "data_struct.h"

#define ONE_DAY 480

int load_data(ArrivalData* data);
void simulation(int numTellers);
double expdist(double mean);

void check_stats(Queue* queue, Time* tellers, Results* result, Time clock);
void add_to_line(Queue* queue, Time clock);
void fill_tellers(Queue* queue, Time* tellers, Results* result);

int main(int argc, char** argv){
  ArrivalData data;
  int result = load_data(&data);

  return result;
}

void simulation(int numTellers){
  //Allocate the tellers and two structs.
  Time* tellerWait = (Time*) calloc(numTellers, sizeof(Time));
  Results result = {0,0,0,0,0};
  Queue queue = {NULL, NULL, 0};

  Time clock = 0;

  while(clock < 480 || queue.size < 0){
    printf("%d\n", clock);    

    ++clock;
  }
  

  
}

void add_to_line(Queue* queue, Time clock){

}

/***********************************************************************
 * Loads the data for the arrival time of customers. This will be used
 * in the simulation to simulate customer arrival times. While loading 
 * the data, a range table is generated for when a roll is made to see
 * if a customer arrives in line. 
 * 
 * Param: data a pointer to the ArrivalData struct the data will be 
 * loaded into. 
 * Return: 0 if all was successful, EIO if there was a problem loading
 * the file. The referenced ArrivalData is returned as well.
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

    //Generate the range
    if(index == 0){
      data->upper_bound[index] = data->percent_data[index];
    }
    else{
      data->upper_bound[index] = 
        (data->upper_bound[index-1] +  data->percent_data[index]);
    }

    printf("%d %d %d\n", data->customers_per_min[index], data->percent_data[index], data->upper_bound[index]);
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

