#ifndef POLYBIUS
#define POLYBIUS
#define SIZE 5
char *pbEncode(const char *plaintext, char table[SIZE][SIZE]);
char *pbDecode(const char *ciphertext, char table[SIZE][SIZE]);
#endif