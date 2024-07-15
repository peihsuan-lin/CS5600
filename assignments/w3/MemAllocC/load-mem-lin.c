/*
 * alloc-mem-lin.c / Memory Management
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Jan 30, 2024
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynblock.h"

int main() {
  const int BLOCKSIZE = 500;
  FILE* ptr;
  char ch;
  ptr = fopen("blocks.data", "r");
  if (ptr == NULL) {
    printf("No files can be open.\n");
    return 1;
  }
  dynBlock* block;
  block = allocDynBlock(BLOCKSIZE);
  int arr[BLOCKSIZE];
  int i = 0;
  int num;
  while (i < block->size && fscanf(ptr, "%d", &num) == 1) {
    arr[i] = num;
    i++;
  }
  storeMem2Blk(arr, block, block->size);
  free(block);
  fclose(ptr);
  return 0;
}