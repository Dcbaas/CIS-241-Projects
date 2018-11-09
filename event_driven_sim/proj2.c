#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <unistd.h>
#include "queue.h"
#include "stats_structs.h"

//This is the avg wait time you gave us
#define AVG_WAIT 2.0

//Here are the macros for the random function
#define INITIAL_SEED 17
#define MULTIPLIER 25273
#define INCREMENT 13849
#define MODULUS 100

//The random fuction reqires a global static variable to work. 
static unsigned int seed = INITIAL_SEED;

/************************************************************************
 * For all function comments refer to the comments below. 
 *********************************************************************/
int simulation(int numTellers);
double expdist(double mean);
unsigned int random_num();
int add_to_line(Queue* queue, Time clock, 
ArrivalData* data, Results* stats);
void fill_tellers(Queue* queue, Time* tellers, 
int numTellers, Results* stats, Time clock);

/**********************************************************************
 * The main function started to program and facilitated running the
 * other functions. Because of how the project is structured. I am
 * not able to error check and return an error in this version of the 
 * program. 
 * 
 * COMMAND LINE ARGUMENT: <numTeller> The number of tellers to be in 
 * this given simulation. 
 *  
 * Returns nothing of use execpt when the argument list is wrong. 
 *********************************************************************/
int main(int argc, char** argv){
  if(argc == 1){
    printf("./simulation <numtellers>\n");
    return 1;
  }


  simulation(atoi(argv[1]));

  return 0;
}

/***********************************************************************
 * The simulation function runs a simulation of a bank through one whole
 * day of work. The independant variable is the number of tellers 
 * on shift for the given day. The simulation is run in part with a 
 * slew of other functions that faclitate individual steps within the 
 * process such as adding people to and from line to printing the end
 * stats on screen. The project instruction calls for this function 
 * to be of type void. I however decided that it would be best for it
 * to return an integer value to allow for error checking 
 * 
 * Param: numTellers The number of tellers on shift for the simulated
 * day at the bank.
 * Return: 0 if the simulation was successful, -1 if the simulation 
 * failed in some way.
 **********************************************************************/
int simulation(int numTellers){
  ArrivalData data;
  int loaded_file = load_data(&data);
  // printf("here0");dd

  Results result;
  // printf("here results");
  int allocated_stats = init_results_struct(&result);

  if(loaded_file == EIO){
    perror("ERROR STARTING SIMULATION: FILE LOAD ERROR");
    free_results_struct(&result);
    return -1;
  }

  if(allocated_stats == ENOMEM){
    perror("ERROR STARTING SIMULATION: STATS STRUCT ALLOCATION FAILURE");
    free_results_struct(&result);
    return -1;
  }

  Time* tellerWait = (Time*) calloc(numTellers, sizeof(Time));

  if(!tellerWait){
    perror("ERROR STARTING SIMULATION: TELLER ALLOCATION FAILURE");
    return -1;
  }

  Queue queue = {NULL, NULL, 0};
  Time clock = 0;

  while(clock < 480 || queue.size > 0) {
    //Check if add line failed. End the simulation if it did.
    if(add_to_line(&queue, clock, &data, &result) == -1){
      perror("SIMULATION FAILED");
      free_results_struct(&result);
      free(tellerWait);
      return -1;
    }  
    fill_tellers(&queue, tellerWait, numTellers, &result, clock);

    ++clock;
  }

  generate_stats(&result, clock);
  print_stats(&result, clock);
  free_results_struct(&result);
  free(tellerWait);
  clear(&queue);

  return 0;
}

/***********************************************************************
 * The add_to_line function facilitates added person to the line at the 
 * bank. It rolls a random number and based on the result of, adds a
 * given amount of people to the queue line. If the program runs out of
 * memory to add to the queue, the function called will print an error
 *  message and return -1 as an error code. At the end of adding
 *  customers to the line, The max length will be checked and updated
 *  as needed. 
 * 
 * Param: queue The Queue having customers added to it.
 * Param: clock The time value for the customers being added to the line.
 * Param: data The Arrival data table used to determine how many 
 * customers arrive in line.
 * Param: stats The stats struct tracking the results of the simulation.
 * Return: 0 if all was successful -1 if there was a memory issue. 
 **********************************************************************/
int add_to_line(Queue* queue, Time clock, 
ArrivalData* data, Results* stats){
  static unsigned int curr_id = 0;
  int success = 0;
  //If it is the end of the day, don't add to the line.
  if(clock < 480){
    //Roll to see how many customers get added
    unsigned int roll = random_num() + 1;

    //Check the result of roll
    for(int arrival_index = 0;
    arrival_index < TABLE_SIZE; ++arrival_index){
      // printf(" %d\n", data->percent_data[arrival_index]);
      if(roll <= data->upper_bound[arrival_index]){
        //Add the perscribed number of customers to the queue
        for(int add = 0; add < data->customers_per_min[arrival_index];
        ++add){
          //Add an error stopper
          success = push(queue, clock, ++curr_id);
        }
        break;
      }
    }   
  }
  //Reallocate clock space if needed 
  if(stats->queue_max_elements < clock){
     success = realloc_queue_stats(stats);
  }

  //Add current queue size to the table
  stats->queue_sizes[clock] = queue->size;

  return success;
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
 int numTellers, Results* stats, Time clock){
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
        Node* temp = getFront(queue);
        stats->time_results[(stats->time_list_size)++] = 
        clock - temp->time;

        //Pop them off the stack and reset the timer
        pop(queue);
        tellers[teller_it] = expdist(AVG_WAIT);
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

/**********************************************************************
 * Creates a seemingly random number better than the random number 
 * function provided by C. In the assignment instruction, it was 
 * suggested to use a version of this better random number generator 
 * function. The function itself reqired a global static variable.
 * Ultimately, it was just as repetitive as the normal rand function.
 * The source code for the original random number generator can be 
 * found on pg. 221-222 of the book on c. When called, 1 is added 
 * to the value of the result to make sure the range is from 1-100.
 * 
 * Return: A random number from 0-99
 *********************************************************************/
unsigned int random_num(){
  seed = (MULTIPLIER * seed + INCREMENT) % MODULUS;
  return seed;
}
