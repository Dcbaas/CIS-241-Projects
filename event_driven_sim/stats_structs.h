#ifndef               DATA_STRUCT_H
#define               DATA_STRUCT_H
#include "queue.h"

#define TABLE_SIZE 5

typedef short Customers;
typedef short Percent;
typedef int Time;

typedef struct ArrivalData{
 Percent percent_data[TABLE_SIZE];
 Customers customers_per_min[TABLE_SIZE];
 unsigned int upper_bound[TABLE_SIZE];
} ArrivalData;

typedef struct Results{
  //Queue size array.
  Customers* queue_sizes;

  //Time stats array.
  Time* time_results;
  size_t time_list_size;
} Results;

#endif

