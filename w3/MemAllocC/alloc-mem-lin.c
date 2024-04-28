/*
 * alloc-mem-lin.c / Memory Management
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Jan 29, 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
// 5 MB of storage from the static segment, will be deallocated while program
// ends
static char staticMemp[5 * 1024 * 1024];
int main() {
  printf("static segment is allocated at %p\n", &staticMemp);

  // 1 MB stack, allocated when main() is called
  char stackMem[1 * 1024 * 1024];
  printf("stack memory is allocated at %p\n", &stackMem);
  // stack memory is freed when main() exits

  // 10 MB heap allocation using malloc, need to be free manually afterwards
  char* heapMem = (char*)malloc(10 * 1024 * 1024);
  if (heapMem == NULL) return -1;
  printf("heap memory is allocated at %p\n", &heapMem);
  free(heapMem);
  return 0;
}