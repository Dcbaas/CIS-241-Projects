#include "queue.h"
#include <stdlib.h>


void init(Queue* queue){
  queue->front = NULL;
  queue->back = NULL;
}

int push(Queue* queue, int value){
  Node* temp = (Node*) malloc(sizeof(Node));
  temp
}

int peek(Queue* queue);

void pop(Queue* queue);
