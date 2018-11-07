#ifndef               DATA_STRUCT_H
#define               DATA_STRUCT_H

#define TABLE_SIZE 5
//The max possible people to come through the line is 1920
#define TIME_TABLE_SIZE 1920

typedef int Customers;
typedef int Percent;
typedef int Time;

typedef struct ArrivalData{
 Percent percent_data[TABLE_SIZE];
 Customers customers_per_min[TABLE_SIZE];
 unsigned int upper_bound[TABLE_SIZE];
} ArrivalData;

typedef struct Results{
  //Queue size array.
  Customers* queue_sizes;

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
void generate_stats(Results* data);
void print_stats(Results* results);
void free_results_struct(Results* results);

#endif

