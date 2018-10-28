#include <stdio.h>
#include "queue.h"

int main(int argc, char** argv){
  const short MAX_TEST = 500;

  Queue test_queue;

  initQueue(&test_queue);

  //Load 500 elements as a test
  for(short number = 0; number < MAX_TEST; ++number){
    if(push(&test_queue, number) == -1){
      fprintf(stderr, "OUT OF MEMORY");
      break;
    }
  }

  //Pop all of the elements
  while(!isEmpty(&test_queue)){
    printf("%d\n", getFront(&test_queue));
    pop(&test_queue);
  }


  return 0;
}
