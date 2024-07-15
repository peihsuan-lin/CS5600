/*
cipher.c / Multiprocessing in C
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Feb 18, 2024
 *
 */
#define SIZE 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "polybius.h"
// The table is a 5 * 5 structure containing the key to 26 alphabets, the
// letters i and j are combined. special characters is ignored.
void createTable(char table[SIZE][SIZE])
{
  char code = 'A';
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (code == 'J')
      {
        code++;
      }
      table[i][j] = code++;
    }
  }
}
int main() {
    char table[SIZE][SIZE];
    createTable(table);

    char input[1024];

    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0;

        char* encrypted = pbEncode(input, table);
        printf("%s\n", encrypted);
        free(encrypted);
    }

    return 0;
}

