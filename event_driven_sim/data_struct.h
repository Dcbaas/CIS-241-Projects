#ifndef               DATA_STRUCT_H
#define               DATA_STRUCT_H

#define TABLE_SIZE 5

typedef short Customers;
typedef short Percent;

typedef struct Data{
 Percent percent_data[TABLE_SIZE];
 Customers customers_per_min[TABLE_SIZE];
} ArrivalData;

#endif

