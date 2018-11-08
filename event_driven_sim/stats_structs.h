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

typedef struct Results{
  //Queue size array.
  Customers* queue_sizes;
  size_t queue_max_elements;

  double avg_queue_size;
  double max_queue_size;

  //Time stats array.
  Time* time_results;

  double avg_time_in_line;
  double max_time_in_line;

  //Also total customers served.
  size_t time_list_size;
} Results;

int load_data(ArrivalData* data);
int init_results_struct(Results* results);
int realloc_queue_stats(Results* results);
void generate_stats(Results* data, int final_time);
void print_stats(Results* results, int final_time);
void free_results_struct(Results* results);

#endif

