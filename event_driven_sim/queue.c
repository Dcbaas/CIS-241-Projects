#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "stats_structs.h"

/***********************************************************************
 * Takes a queue and initializes its values to an empty list. I am 
 * unsure of the state of the queue when it is declared without 
 * definition so I set the definition.
 *
 * Param: queue. The pointer to the Queue being initalized.
 **********************************************************************/
void initQueue(Queue* queue){
  queue->front = NULL;
  queue->back = NULL;
  queue->size = 0;
}

/***********************************************************************
 * Checks to see if the queue is empty it does this by checking the size
 * value of the queue passed in.
 *
 * Param: queue The pointer to the Queue being checked.
 * Return: 1 if the queue is empty and 0 otherwise.
 **********************************************************************/
int isEmpty(Queue* queue){
  return queue->size == 0;
}

/***********************************************************************
 * Takes a new element and pushes it onto the back of the queue.
 *
 * There are muliple scnarios of state for pushing to this queue.
 *
 * 1. The queue is empty and needs to be handled differently in
 * the push.
 * 2. The queue has only one element in it.
 * 3. More than one element in the queue. 
 *
 * Param queue The Queue the new element is being placed on.
 * Param time The time value for the new element being placed on the
 * queue.
 * Return 1 if the push was successful, -1 if there was a failure due
 * to lack of memory.
 *********************************************************************/
int push(Queue* queue, Time time, unsigned short id){
  //Create the Node
  Node* temp = (Node*) malloc(sizeof(Node));
  if(!temp){
    fprintf(stderr, "ERROR NOT ENOUGH MEMORY FOR NODE");
    return -1; //Change to use errno lib.
  }

  temp->time = time;
  temp->next = NULL;
  temp->ID = id;

  switch(queue->size){
    case 0:{
             queue->front = temp;
             queue->back = temp;
             ++(queue->size);
             break;
           }
    default:{
              queue->back->next = temp;
              queue->back = temp;
              ++(queue->size);
              break;
            }
  }
  
  return 0;
}

/***********************************************************************
 * Takes a look at the value of the top element on the queue. This
 * action only looks at the first element. It does not take it off.
 *
 * Param: queue The Queue being looked at for this operation.
 * Return: A pointer to the first Node in the queue. If the queue is 
 * empty, NULL is returned. 
 **********************************************************************/
Node* getFront(Queue* queue){
  Node* value = NULL;
  if(!isEmpty(queue)){
    value  = queue->front;
  }
  return value;
}

/***********************************************************************
 * Removes the element at the front of the Queue. This does not return
 * the value of the element removed from the queue. Use the getFront
 * function to perform that operation.
 *
 * Cases for the pop operation are:
 * 1. The list is empty in which case don't do anything. 
 * 2. The list has one element in it in which case the end pointers
 * have to be set to NULL
 * 3. The list has multiple elements in it.
 *
 * Param: queue The queue being used in this operation
 **********************************************************************/
void pop(Queue* queue){
  Node* temp = queue->front;

  //Don't do anything if the list is empty
  if(isEmpty(queue)){
    fprintf(stderr, "List is Empty");
    return;
  }
  else if(queue->size == 1){
    queue->front = NULL;
    queue->back = NULL;
    free(temp);
    --(queue->size);
  }
  else{
    queue->front = temp->next;
    free(temp);
    --(queue->size);
  }
}

