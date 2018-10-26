#include <stdlib.h>
#include "queue.h"

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
int push(Queue* queue, Time time);

/***********************************************************************
 * Takes a look at the value of the top element on the queue. This
 * action only looks at the first element. It does not take it off.
 *
 * Param: queue The Queue being looked at for this operation.
 * Return The time value of the top element.
 * TODO Add a error check for an empty queue.
 **********************************************************************/
Time getFront(Queue* queue);

/***********************************************************************
 * Removes the element at the front of the Queue. This does not return
 * the value of the element removed from the queue. Use the getFront
 * function to perform that operation.
 *
 * Param: queue The queue being used in this operation
 **********************************************************************/
void pop(Queue* queue);
