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
  Customers total_served;

  unsigned int time_data_points;
  Time time_data_total;
  Time avg_wait;
  Time max_wait;

  unsigned int line_data_points;
  Customers customer_data_total;
  Customers avg_line_length;
  Customers max_line_length;
} Results;

#endif

