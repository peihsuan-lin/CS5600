#include "letterConvert.h"
#include <stdio.h>
int checkName(char *name1, char *name2) {
  int i = 0;
  while (*name1 && *name2) {
    if (*name1 != *name2) {
      return -1;
    }
    name1++;
    name2++;
  }
  return (*name1 == '\0' && *name2 == '\0') ? 1 : -1;
}