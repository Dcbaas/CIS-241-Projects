#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "stats_structs.h"

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
  }

  fclose(input_file);
  return 0;
}

/**********************************************************************
 * Initializes the results struct to track data for the simulation.
 * If there is not enough memory then the function will fail.
 * 
 * Param: results The struct being initialized
 * Return: 0 if all was successful, ENOMEM if there was not enough 
 * memory for the struct.
 **********************************************************************/
int init_results_struct(Results* results){
    // printf("here1");
    results->queue_sizes = (Customers*) malloc(480 * sizeof(Customers));
    results->time_results = (Time*) malloc(TIME_TABLE_SIZE * sizeof(Time));

    //Check if allocation was successful
    if(!results->queue_sizes || !results->time_results){
        perror("ERROR: NOT ENOUGH MEMORY FOR RESULTS STRUCT");
        free(results->queue_sizes);
        free(results->time_results);
        return ENOMEM;
    }
    results->avg_queue_size = 0.0;
    results->avg_time_in_line = 0.0;
    results->max_queue_size = 0.0;
    results->max_time_in_line = 0.0;

    results->time_list_size = 0;
    results->queue_max_elements = ONE_DAY;
    return 0;
}

/**********************************************************************
 * Takes the queue_sizes data and reallocates more space for the array
 * This will be called if the array of queue sizes outstrips the 
 * allocated space for it.
 * 
 * Param: results The results struct with the queue_sizes array that
 * will be reallocated.
 * Return: 0 if all was successful. -1 if the reallocation failed. 
 *********************************************************************/
int realloc_queue_stats(Results* results){
    Customers* temp_sizes = 
    (Customers*) 
    malloc(results->queue_max_elements*2 * sizeof(Customers));

    if(!temp_sizes){
        perror("REALLOCATION FAILED");
        return -1;
    }

    for(int index = 0; index < results->queue_max_elements; ++index){
        temp_sizes[index] = results->queue_sizes[index];
    }


    results->queue_max_elements *= 2;
    free(results->queue_sizes);
    results->queue_sizes = temp_sizes;
    return 0;
}

/**********************************************************************
 * Generates the stats from the simulation using the data collected.
 * 
 * Param: data The Results struct holding the data.
 **********************************************************************/
void generate_stats(Results* data){
    data->max_queue_size = 0;
    //Generate queue stats.
    for(int index = 0; index < data->queue_max_elements; ++index){
        //Check the max.
        if(data->max_queue_size < data->queue_sizes[index]){
            data->max_queue_size = data->queue_sizes[index];
        }
        //Add to the avg stats.
        data->avg_queue_size += data->queue_sizes[index];
    }    
    //Calc the avg.
    data->avg_queue_size /= data->queue_max_elements;

    //Generate time stats.
    for(int index = 0; index < data->time_list_size; ++index){
        //Check the max
        if(data->max_time_in_line < data->time_results[index]){
            data->max_time_in_line = data->time_results[index];
        }
        //Add to the avg stats.
        data->avg_time_in_line += data->time_results[index];
    }
    //Calc avg time in line.
    data->avg_time_in_line /= data->time_list_size;
}

/**********************************************************************
 * Prints the statistics on the screen
 * 
 * Param: results The results being printed on the screen.
 **********************************************************************/
void print_stats(Results* results){
    printf("Total Served: %zu\n\n", results->time_list_size);
    printf("Average Line Size: %f\n", results->avg_queue_size);
    printf("Max Line Size: %f\n\n", results->max_queue_size);
    printf("Average Wait Time: %f\n", results->avg_time_in_line);
    printf("Max Time in Line: %f\n", results->max_time_in_line);
    printf("////////////\n\n");
}

/**********************************************************************
 * This function frees the data from the results struct.
 * 
 * Param: results The struct having data freed.
 **********************************************************************/
void free_results_struct(Results* results){
    free(results->queue_sizes);
    free(results->time_results);
}