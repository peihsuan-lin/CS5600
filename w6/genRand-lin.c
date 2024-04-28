/*
 * genRand-lin.c / Multiprocessing in C
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Feb 17, 2024
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

int genRand(int lowerBound, int upperBound)
{
  seed = (a * seed + c) % m;
  return lowerBound + (seed % (upperBound - lowerBound + 1));
}
/*
This program generates small text strings and write then to output.txt file
*/
int main()
{
  const char *file_name = "output.txt";
  const int number = 10000;
  FILE *fptr;
  FILE *ptr;
  initSeed();
  ptr = fopen(file_name, "w");
  if (ptr == NULL)
  {
    printf("Unable to open file");
    return 1;
  }
  for (int i = 0; i < number; i++)
  {
    int word_len = genRand(2, 8);
    char *word = (char *)malloc(word_len * sizeof(char));
    for (int j = 0; j < word_len; j++)
    {
      word[j] = genRand(97, 122);
    }
    fprintf(ptr, "%s\n", word);
  }
  fclose(ptr);
}
