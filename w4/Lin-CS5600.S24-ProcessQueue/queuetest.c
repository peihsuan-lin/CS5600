#include <stdio.h>
#include "queue.h"

void printQueue(queue_t* queue) {
  node_t* current = queue->head;
  while (current != NULL) {
    process_t* process = (process_t*)current->data;
    printf("[ID: %d, Name: %s, Runtime: %ld, Priority: %d] ",
           process->identifier, process->name, process->runtime,
           process->priority);
    current = current->next;
  }
  printf("\n");
}
void testGeneralElements() {
  printf("Testing General Elements\n");
  queue_t myQueue;
  initQueue(&myQueue);

  process_t p1 = {1, "Task1", 100, 5};
  process_t p2 = {2, "Task2", 200, 4};

  printf("Adding p1 process...\n");
  add2q(&myQueue, &p1);
  printQueue(&myQueue);  // Print after adding first element

  printf("Adding p2 process...\n");
  add2q(&myQueue, &p2);
  printQueue(&myQueue);  // Print after adding second element

  printf("Removing the p1 from the queue...\n");
  popQ(&myQueue);
  printQueue(&myQueue);
}

void testElementsWithPriorities() {
  printf("Testing Elements With Priorities\n");
  queue_t myQueue;
  initQueue(&myQueue);

  process_t p1 = {1, "HighPriority", 300, 1};
  process_t p2 = {2, "MediumPriority", 400, 2};
  process_t p3 = {3, "LowPriority", 500, 3};

  printf("Adding 3 processes to the queue...\n");
  add2q(&myQueue, &p3);
  add2q(&myQueue, &p2);
  add2q(&myQueue, &p1);
  printQueue(&myQueue);
  printf("Removing the highest priority process...\n");
  rmProcess(&myQueue);
  printQueue(&myQueue);
}

int main() {
  testGeneralElements();
  testElementsWithPriorities();
}