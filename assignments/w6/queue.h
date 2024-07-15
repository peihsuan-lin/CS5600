#ifndef QUEUE_H
#define QUEUE_H
typedef struct node_t {
  void* data;
  struct node_t* next;
  struct node_t* prev;
} node_t;
typedef struct {
  int identifier;
  char* name;
  long runtime;
  int priority;
} process_t;
typedef struct {
  node_t* head;
  node_t* tail;
  int size;
} queue_t;

void initQueue(queue_t* queue);
void add2q(queue_t* queue, void* element);
void* popQ(queue_t* queue);
process_t* rmProcess(queue_t* queue);
#endif