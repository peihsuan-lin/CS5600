#include <stdio.h>

void toCap(char *str) {
  if (*str >= 97 && *str <= 122) {
    *str -= 'a' - 'A';
  }
}
void toUpper(char *str) {
  while (*str) {
    if (*str >= 97 && *str <= 122) {
      *str -= 'a' - 'A';
    }
    str++;
  }
}
void toLower(char *str) {
  while (*str) {
    if (*str >= 65 && *str <= 90) {
      *str += 'a' - 'A';
    }
    str++;
  }
}