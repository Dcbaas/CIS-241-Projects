#include <stdlib.h>
#include "queue.h"

int push(Queue* queue, Time time){
  Node* temp = (Node*) malloc(sizeof(Node));
  if(temp == NULL){
    return -1;
  }

  temp->time = time;
  temp->next = NULL;

  queue->back = temp;
  return 1;
}

Time getFront(Queue* queue){
}

void pop(Queue* queue){

}
