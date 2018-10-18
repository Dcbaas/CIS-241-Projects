#ifndef       QUEUE_H
#define       QUEUE_H

/* I use a typdef to demark a time variable for readability.*/
typedef int Time;

/***********************************************************************
 * A Linked List is composed of nodes and connections to other nodes.
 * In this case the linked list is a singly linked list. Therefore
 * the struct Node reflects this decision. This Node type is specialized 
 * for the simulation. It holds a Time value determining when the 
 * node should be removed from the data structure it was put onto.
 *
 * Member: time A time value for when this node is removed from the
 * data structure.
 * Member: next The next Node in the Linked List following this 
 * node.
 **********************************************************************/
typedef struct Node {
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
} Queue;

/***********************************************************************
 * Takes a new element and pushes it onto the back of the queue 
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

#endif

