#include <stdlib.h>

typedef struct Node{
  int value;
  struct Node* next;
} Node;

typedef struct Queue {
  Node* front;
  Node* back;
  int size;
} Queue; 

void init(Queue* queue);

int push(Queue* queue, int value);

int peek(Queue* queue);

void pop(Queue* queue);
