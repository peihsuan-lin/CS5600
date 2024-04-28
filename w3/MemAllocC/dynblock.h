#ifndef DYNBLOCK
#define DYNBLOCK

typedef struct {
  int* data;
  int size;
} dynBlock;

dynBlock* allocDynBlock(int size);
void storeMem2Blk(int* arr, dynBlock* ptr, int size);

#endif