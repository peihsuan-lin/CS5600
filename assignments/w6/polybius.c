#include "polybius.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5
/*
 Encodes the plaintext using the Polybius square cipher.
*/
char *pbEncode(const char *plaintext, char table[SIZE][SIZE]) {
  const char *c = plaintext;
  int len = strlen(plaintext);
  char *encode = malloc(sizeof(char) * len * 2 + 1);
  int encode_idx = 0;
  for (int idx = 0; idx < len; idx++) {
    char ch = toupper(plaintext[idx]);
    if (isalpha(ch)) {
      if (ch == 'J') ch = 'I';
      for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
          if (ch == table[i][j]) {
            encode[encode_idx++] = '1' + i;
            encode[encode_idx++] = '1' + j;
            break;
          }
        }
      }
    }
    // ignore special character
    else {
      encode[encode_idx++] = plaintext[idx];
    }
  }
  encode[encode_idx] = '\0';
  return encode;
}

// Decodes the ciphertext using the Polybius square cipher.
char *pbDecode(const char *ciphertext, char table[SIZE][SIZE]) {
  int len = strlen(ciphertext);
  char *decode = malloc(sizeof(char) * len + 1);
  int decode_idx = 0;
  for (int i = 0; i < len; i++) {
    if (isdigit(ciphertext[i]) && isdigit(ciphertext[i + 1])) {
      decode[decode_idx++] = e
          table[ciphertext[i] - '1'][ciphertext[i + 1] - '1'];
      i++;
    } else {
      // special character
      decode[decode_idx++] = ciphertext[i];
    }
  }
  decode[decode_idx] = '\0';
  return decode;
}