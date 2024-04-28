/*
cipher.c / Create Cipher
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Feb 5, 2024
 *
 */
#define SIZE 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "polybius.h"
// The table is a 5 * 5 structure containing the key to 26 alphabets, the
// letters i and j are combined. special characters is ignored.
void createTable(char table[SIZE][SIZE]) {
  char code = 'A';
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (code == 'J') {
        code++;
      }
      table[i][j] = code++;
    }
  }
}
int main(int argc, char const *argv[]) {
  if (argc != 3) {
    printf("Usage: %s -e|-d \"text\"", argv[0]);
    return 1;
  }
  char table[SIZE][SIZE];
  createTable(table);
  const char *flag = argv[1];
  const char *text = argv[2];

  if (strcmp(flag, "-e") == 0) {
    printf("%s\n", pbEncode(text, table));
  } else if (strcmp(flag, "-d") == 0) {
    printf("%s\n", pbDecode(text, table));
  } else {
    printf("Invalid flag provided. Use -e for encryption, -d for decryption.");
    return 1;
  }
  return 0;
}
