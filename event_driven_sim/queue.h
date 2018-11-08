#ifndef       QUEUE_H
#define       QUEUE_H
#include "stats_structs.h"

/***********************************************************************
 * A Linked List is composed of nodes and connections to other nodes.
 * In this case the linked list is a singly linked list. Therefore
 * the struct Node reflects this decision. This Node type is specialized 
 * for the simulation. It holds a Time value determining when the 
 * node should be removed from the data structure it was put onto.
 *
 * Member: ID: The id of the node in the queue. Will generally in order
 * it went into line.
 * Member: time The length of time it took to remove this node from the 
 * data strucure
 * Member: next The next Node in the Linked List following this 
 * node.
 **********************************************************************/
typedef struct Node {
  unsigned short ID;
  Time time;
  struct Node* next;
} Node;

/**********************************************************************
 * A Queue is a data structure that works as it sound. It follows the 
 * First In First Out concept that defines how queues work in real 
 * life. This Queue is implemented using a singly linked list. 
 * For design reasons I have pointers pointing to the front and the back
 * of the queue to make it easy to pop and push to the list. 
 *********************************************************************/
typedef struct Queue{
  Node* front;
  Node* back;
  unsigned int size;
} Queue;

/***********************************************************************
 * Takes a queue and initializes its values to an empty list. 
 * 
 * Param: queue. The Queue being initalized. 
 **********************************************************************/
void initQueue(Queue* queue);

/***********************************************************************
 * Checks to see if the queue is empty it does this by checking the size
 * value of the queue passed in.
 *
 * Param: queue The Queue being initialized. 
 * Return: 1 if the queue is empty and 0 otherwise. 
 **********************************************************************/
int isEmpty(Queue* queue);

/***********************************************************************
 * Takes a new element and pushes it onto the back of the queue 
 *
 * Param queue The Queue the new element is being placed on.
 * Param time The time value for the new element being placed on the
 * queue.
 * Return 1 if the push was successful, -1 if there was a failure due
 * to lack of memory.
 *********************************************************************/
int push(Queue* queue, Time time, unsigned short id);

/***********************************************************************
 * Gets the top Node and returns a pointer to the user. From there its 
 * values can be extracted. 
 * Param: queue The Queue being looked at for this operation.
 * Return: A pointer to the Node at the front of the queue. 
 **********************************************************************/
Node* getFront(Queue* queue);

/***********************************************************************
 * Removes the element at the front of the Queue. This does not return
 * the value of the element removed from the queue. Use the getFront 
 * function to perform that operation.
 *
 * Param: queue The queue being used in this operation
 **********************************************************************/
void pop(Queue* queue);

/**********************************************************************
 * Clears a queue of all elements. This was used in testing to 
 * clear data before a flushed out tellers function was made. 
 * 
 * Param: queue The Queue having its data cleared.
 **********************************************************************/
void clear(Queue* queue);

#endif

