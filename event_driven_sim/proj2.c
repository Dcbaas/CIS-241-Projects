#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "queue.h"
#include "stats_structs.h"

#define ONE_DAY 480

/************************************************************************
 * For all function comments refer to the comments below. 
 *********************************************************************/
int load_data(ArrivalData* data);
void simulation(int numTellers);
double expdist(double mean);
void add_to_line(Queue* queue, Time clock, 
ArrivalData* data, Results* stats);
void fill_tellers(Queue* queue, Time* tellers, 
int numTellers, Results* stats);

int main(int argc, char** argv){
  ArrivalData data;
  int result = load_data(&data);

  return result;
}

void simulation(int numTellers){
  //Allocate the tellers and two structs.
  Time* tellerWait = (Time*) calloc(numTellers, sizeof(Time));
  Results result = {0,0,0,0,0,0,0};
  Queue queue = {NULL, NULL, 0};

  Time clock = 0;

  while(clock < 480 || queue.size < 0){
    printf("%d\n", clock);    

    ++clock;
  }
  

  
}

/***********************************************************************
 * The add_to_line function facilitates added person to the line at the 
 * bank. It rolls a random number and based on the result of, adds a
 * given amount of people to the queue line. If the program runs out of
 * memeory to add to the queue, the program will print a failure messeage
 * indicating the simulation failed due to memory. At the end of 
 * adding customers to the line, stats pertaining to the length of the
 * line. will be updated. 
 * 
 * Param: queue The Queue having customers added to it.
 * Param: clock The time value for the customers being added to the line.
 * Param: data The Arrival data table used to determine how many 
 * customers arrive in line.
 * Param: stats The stats struct tracking the results of the simulation.
 **********************************************************************/
void add_to_line(Queue* queue, Time clock, 
ArrivalData* data, Results* stats){
  //If it is the end of the day, don't add to the line.
  if(clock >= 480)
    return;
  static total_added = 0;
  //Roll a number from 0 - 100 to add people to the line.
  unsigned int rand_num = (rand() % 100) + 1;
  
  //Iterate over the arrival data table to see if the roll matches
  //Somthing in one of the given ranges.
  for(int index = 0; index < TABLE_SIZE; ++index){
    //If it matches the range add the specified amount of people to the 
    //line. If we fail to add to line indicate the simulation is failing
    if(rand_num < data->upper_bound[index]){
      for(Customers added = 0; added < data->customers_per_min; ++added){
        if(push(queue, clock, ++total_added) == -1){
          perror("SIMULATION FAILURE: RAN OUT OF MEMEORY");
          return;
        }
      }
    }
  }

  //Check the line statistics
  //Update the avg line length and the number of data points
  //avg lethgt = total / data point
  //TODO: Add this functionality to stats struct

  //Update the max length if needed
  if(stats->max_line_length < queue->size){
    stats->max_line_length = queue->size;
  }
}

/**********************************************************************
 * The fill_tellers function simulates tellers receiving customers
 * and helping them out. It pops customers out of line and updates the
 * time statistics. In the teller array, the wait time for each 
 * element is updated to reflect the amount of time until the next 
 * customer is served. 
 * 
 * Param: queue The line of people being taken from.
 * Param tellers The tellers stations that are used to serve the 
 * customers.
 * Param: stats The stats struct tracking the results of the simulation. 
 **********************************************************************/
void fill_tellers(Queue* queue, Time* tellers,
 int numTellers, Results* stats){
  //Iterate through all the tellers to see if check availiblity and
  //serve customers
  for(Time* teller = teller < tellers + numTellers; ++ teller){
    //Check the tellers Availiblity. 
    //The teller is ready for the next customer
    if(*teller == 0){
      //Get the stats from the next person in line.
      ++(stats->total_served);
      //update the avg wait time
      //avg wait = total / data points

    }
  }
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

    printf("%d %d %d\n", data->customers_per_min[index], 
    data->percent_data[index], data->upper_bound[index]);
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
