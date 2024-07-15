/*
 * queue.c / Implement Process Queue
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Feb 6, 2024
 *
 */
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

//  set up a new queue instance
void initQueue(queue_t* queue) {
  if (queue != NULL) {
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
  }
}
// adds one instance of an element to the end of the passed queue
void add2q(queue_t* queue, void* element) {
  node_t* newNode = (node_t*)malloc(sizeof(node_t));
  newNode->data = element;
  newNode->next = NULL;
  newNode->prev = queue->tail;
  if (queue->tail != NULL) {
    queue->tail->next = newNode;
  } else {
    queue->head = newNode;
  }
  queue->tail = newNode;
  queue->size++;
}
// removes and returns the data within the element at the front of the queue.
void* popQ(queue_t* queue) {
  node_t* removeNode = (node_t*)malloc(sizeof(node_t));
  removeNode = queue->head;
  void* data = removeNode->data;
  queue->head = removeNode->next;
  queue->head->prev = NULL;
  free(removeNode);
  queue->size--;
  return data;
}
// removes and returns the process with the highest priority in the queue.
process_t* rmProcess(queue_t* queue) {
  if (queue->size == 0) {
    return NULL;
  }
  node_t* cur = queue->head;
  node_t* highestPriNode = cur;
  process_t* highestPriProcess = (process_t*)highestPriNode->data;
  while (cur) {
    process_t* curProcess = (process_t*)cur->data;
    if (curProcess->priority < highestPriProcess->priority) {
      highestPriProcess = curProcess;
      highestPriNode = cur;
    }
    cur = cur->next;
  }
  if (highestPriNode->prev != NULL) {
    highestPriNode->prev->next = highestPriNode->next;
  } else {
    // current head is highestPriority
    queue->head = highestPriNode->next;
  }
  if (highestPriNode->next != NULL) {
    highestPriNode->next->prev = highestPriNode->prev;
  } else {
    queue->tail = highestPriNode->prev;
  }
  queue->size--;
  free(highestPriNode);
  return highestPriProcess;
}
// returns the number of elements in the queue; 0 if the queue is empty.
int qsize(queue_t* queue) {
  if (queue == NULL) return 0;
  return queue->size;
}