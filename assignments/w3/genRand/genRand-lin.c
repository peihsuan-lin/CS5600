/*
 * genRand-lin.c / Random Number Generation
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Jan 30, 2024
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned int seed;
const unsigned long long m = 4294967296;
const unsigned long long a = 1664525;
const unsigned long long c = 1013904223;

void initSeed() { seed = (unsigned int)time(NULL); }

int genRand(int lowerBound, int upperBound) {
  seed = (a * seed + c) % m;
  return lowerBound + (seed % (upperBound - lowerBound + 1));
}

int main(int argc, char *argv[]) {
  if (argc != 3 && argc != 4) {
    printf("Usage: %s <number> <filename>\n", argv[0]);
    return 1;
  }
  const char *file_name = argv[2];
  const int number = atoi(argv[1]);
  FILE *fptr;
  FILE *ptr;
  initSeed();
  if (argc == 4 && !strcmp(argv[3], "-a")) {
    fptr = fopen(file_name, "a");
    if (fptr == NULL) {
      printf("Unable to open file");
      return 1;
    }
    for (int i = 0; i < number; i++) {
      fprintf(fptr, "%d\n", genRand(1, 100));
    }
    fclose(fptr);
  } else if (argc == 3) {
    ptr = fopen(file_name, "w");
    if (ptr == NULL) {
      printf("Unable to open file");
      return 1;
    }
    for (int i = 0; i < number; i++) {
      fprintf(ptr, "%d\n", genRand(1, 100));
    }
    fclose(ptr);
  } else {
    printf("Usage: %s <number> <filename>[ -a]\n", argv[0]);
    return 1;
  }
}
