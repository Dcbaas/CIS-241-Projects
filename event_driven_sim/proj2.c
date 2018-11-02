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
void updateAverages(Results* stats);

int main(int argc, char** argv){

  simulation(4);
  return 0;
}

void simulation(int numTellers){
  ArrivalData data;
  int load = load_data(&data);

  //Allocate the tellers and two structs.
  Time* tellerWait = (Time*) calloc(numTellers, sizeof(Time));
  Results result = {0,0,0,0,0,0,0};
  Queue queue = {NULL, NULL, 0};

  Time clock = 0;

  printf("The init size: %d\n", queue.size);

  while(clock < 480) {
    // printf("%d\n", clock);  

    add_to_line(&queue, clock, &data, &result);  

    ++clock;
  }

  printf("The final size: %d\n", queue.size);
  clear(&queue);
  printf("The last size: %d\n", queue.size);
  

  
}

/***********************************************************************
 * The add_to_line function facilitates added person to the line at the 
 * bank. It rolls a random number and based on the result of, adds a
 * given amount of people to the queue line. If the program runs out of
 * memeory to add to the queue, the program will print a failure messeage
 * indicating the simulation failed due to memory. At the end of 
 * adding customers to the line, The max length will be checked
 * and updated as needed.
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
  if(clock < 480){
    //Add one to the total num of data points
    ++(stats->line_data_points);

    //Roll to see how many customers get added
    //TODO refer to book for better rand. This will be the same
    //every time.
    unsigned char roll = (rand() % 100) + 1;

    //Check the result of roll
    for(int arrival_index = 0;
    arrival_index < TABLE_SIZE; ++arrival_index){
      if(roll <= data->percent_data[arrival_index]){
        //Add the prescribed number to the data_points_total
        stats->line_data_points += data->customers_per_min[arrival_index];
        //Add the perscribed number of customers to the queue
        for(int add = 0; add < data->customers_per_min[arrival_index];
        ++add){
          //Add an error stopper
          push(queue, clock, stats->line_data_points);
        }
        break;
      }
    }   
  }

  //Update the max
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
