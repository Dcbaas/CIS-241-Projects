#ifndef               DATA_STRUCT_H
#define               DATA_STRUCT_H
#include "queue.h"

#define TABLE_SIZE 5

typedef short Customers;
typedef short Percent;
typedef int Time;

typedef struct Data{
 Percent percent_data[TABLE_SIZE];
 Customers customers_per_min[TABLE_SIZE];
 unsigned int upper_bound[TABLE_SIZE];
} ArrivalData;

typedef struct Results{
  Customers total_served;
  Time avg_wait;
  Time max_wait;
  unsigned int avg_line_length;
  unsigned int max_line_length;


} Results;

#endif

