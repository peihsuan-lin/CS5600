#include "dynblock.h"
#include <stdio.h>
#include <stdlib.h>

dynBlock* allocDynBlock(int size) {
  dynBlock* ptr = (dynBlock*)malloc(sizeof(dynBlock));
  if (ptr == NULL) return NULL;
  ptr->data = (int*)malloc(size * sizeof(int));
  if (ptr->data == NULL) {
    free(ptr);
    return NULL;
  }
  ptr->size = size;
  return ptr;
}
void storeMem2Blk(int* arr, dynBlock* ptr, int size) {
  for (int i = 0; i < size; i++) {
    ptr->data[i] = arr[i];
  }
}