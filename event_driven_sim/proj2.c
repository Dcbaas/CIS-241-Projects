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
void simulation(int numTellers);
double expdist(double mean);
void add_to_line(Queue* queue, Time clock, 
ArrivalData* data, Results* stats);
void fill_tellers(Queue* queue, Time* tellers, 
int numTellers, Results* stats);
void updateAverages(Results* stats);

/**********************************************************************
 * The main function started to program and facilitated running the
 * other functions. Because of how the project is structured. I am
 * not able to error check and return an error in this version of the 
 * program. 
 * 
 * NO COMMAND LINE ARGUMENTS. 
 * RETURNS 0. 
 *********************************************************************/
int main(int argc, char** argv){

  simulation(4);
  return 0;
}

void simulation(int numTellers){
  ArrivalData data;
  int load = load_data(&data);

  //Allocate the tellers and two structs.
  Time* tellerWait = (Time*) calloc(numTellers, sizeof(Time));
  Results result;
  Queue queue = {NULL, NULL, 0};

  Time clock = 0;

  printf("The init size: %d\n", queue.size);

  while(clock < 480) {
    // printf("%d\n", clock);  

    add_to_line(&queue, clock, &data, &result);  
    fill_tellers(&queue, tellerWait, numTellers, &result);

    ++clock;
  }

  printf("The final size: %d\n", queue.size);
  clear(&queue);

  
}

/***********************************************************************
 * The add_to_line function facilitates added person to the line at the 
 * bank. It rolls a random number and based on the result of, adds a
 * given amount of people to the queue line. If the program runs out of
 * memory to add to the queue, the program will print a failure message
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
  static unsigned int curr_id = 0;
  //If it is the end of the day, don't add to the line.
  if(clock < 480){
    //Roll to see how many customers get added
    //TODO refer to book for better rand. This will be the same
    //every time.
    unsigned char roll = (rand() % 100) + 1;

    //Check the result of roll
    for(int arrival_index = 0;
    arrival_index < TABLE_SIZE; ++arrival_index){
      if(roll <= data->percent_data[arrival_index]){
        //Add the perscribed number of customers to the queue
        for(int add = 0; add < data->customers_per_min[arrival_index];
        ++add){
          //Add an error stopper
          push(queue, clock, ++curr_id);
        }
        break;
      }
    }   
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
   //Cycle through each teller to see if they are available 
   for(int teller_it = 0; teller_it < numTellers; ++teller_it){
     //The teller is busy. Increment the time down by one
     if(tellers[teller_it] > 0){
       --tellers[teller_it];
     }
     //The teller is ready to serve 
     else{
       //Are there people in line?
       if(!isEmpty(queue)){
        //TODO read the time the person in line got in and calculate 
        //their wait time
        //Pop them off the stack and reset the timer
        pop(queue);
        tellers[teller_it] = expdist(2.0);
       }
     }
   }

}

/**********************************************************************
 * Simulates the amount of time it takes to serve one customer at the 
 * counter. The result of this will be stored in a teller array slot 
 * to signify that the teller is busy. As an observation, the time is 
 * measured in integers but the prompt for this function is defined as a
 * double return value. Don't know what to make of that.
 *
 * Param mean The avg time it takes to serve on customer.
 * Return a random duration it will take to serve a customer. 
 **********************************************************************/
double expdist(double mean){
  double random_num = rand();
  random_num /= RAND_MAX;
  return -mean * log(random_num);
}
