#ifndef               DATA_STRUCT_H
#define               DATA_STRUCT_H

//The table size for the arrival data will have 5 elements in it.
#define TABLE_SIZE 5

//The max possible people to come through the line is 1920
#define TIME_TABLE_SIZE 1920

//One 8 hour day.
#define ONE_DAY 480

//I used typdefs to make understanding some of the program easier.  
typedef int Customers;
typedef int Percent;
typedef int Time;

/**********************************************************************
 * The ArrivalData struct is used to store the proj2.dat data from the
 * file It has fields for all variables specified in the assignment.
 * The upper_bound data is derived from the percent data in the loading
 * function. 
 **********************************************************************/
typedef struct ArrivalData{
 Percent percent_data[TABLE_SIZE];
 Customers customers_per_min[TABLE_SIZE];
 unsigned int upper_bound[TABLE_SIZE];
} ArrivalData;

/**********************************************************************
 * The Results struct tracks the statisctics for the simulation. 
 * It tracks the queue's size and the time data for each customer.
 * It also tracks averages and max values for each data point. Those 
 * data points are doubles to allow for more accurate data. 
 * Also in the struct are size values for the arrays. 
 * The queue_max_size keeps track of the size of the data structure 
 * rather than the size of the data points. time_list_size also serves
 * as the total customers served due to each customer being recored
 * in that stat.
 *********************************************************************/
typedef struct Results{
  //Queue size array.
  Customers* queue_sizes;
  //The size of the queue_sizes data structure. 
  size_t queue_max_elements;

  //Average and Max stats for queue sizes.
  double avg_queue_size;
  double max_queue_size;

  //Time stats array.
  Time* time_results;

  //Average and max Time in line stats
  double avg_time_in_line;
  double max_time_in_line;

  //Also total customers served.
  size_t time_list_size;
} Results;

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
int load_data(ArrivalData* data);

/**********************************************************************
 * Initializes the results struct to track data for the simulation.
 * If there is not enough memory then the function will fail.
 * 
 * Param: results The struct being initialized
 * Return: 0 if all was successful, ENOMEM if there was not enough 
 * memory for the struct.
 **********************************************************************/
int init_results_struct(Results* results);

/**********************************************************************
 * Takes the queue_sizes data and reallocates more space for the array
 * This will be called if the array of queue sizes outstrips the 
 * allocated space for it.
 * 
 * Param: results The results struct with the queue_sizes array that
 * will be reallocated.
 * Return: 0 if all was successful. -1 if the reallocation failed. 
 *********************************************************************/
int realloc_queue_stats(Results* results);

/**********************************************************************
 * Generates the stats from the simulation using the data collected.
 * 
 * Param: data The Results struct holding the data.
 **********************************************************************/
void generate_stats(Results* data, int final_time);

/**********************************************************************
 * Prints the statistics on the screen
 * 
 * Param: results The results being printed on the screen.
 **********************************************************************/
void print_stats(Results* results, int final_time);

/**********************************************************************
 * This function frees the data from the results struct.
 * 
 * Param: results The struct having data freed.
 **********************************************************************/
void free_results_struct(Results* results);

#endif
