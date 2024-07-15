/*
 * LinP.CS5600.CmdArgsC.c / Command Line Arguments 
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Jan 29, 2024
 *
 */
#include <stdio.h>
#include "checkArgs.h"
#include "letterConvert.h"

int main(int argc, char *argv[]) {
  char *name = argv[0];
  char *targetName = "arger-lin";
  char *flag = argv[1];
  if (argc < 3) {
    printf("At least 3 args is required. Usage: ./arger-lin <-flag> <words>\n");
    return -1;
  }
  typedef void (*Operation)(char*);

  Operation operation = NULL; 

  if (checkName(flag, "-u") == 1) {
    operation = toUpper;
  }
  else if (checkName(flag, "-l") == 1) {
    operation = toLower;
  }
  else if (checkName(flag, "-cap") == 1) {
    operation = toCap;
  }
  else {
    printf("invalid flags provided\n");
    return -1;
  }
  for (int i = 2; i < argc; i++) {
    operation(argv[i]);
    printf("%s ", argv[i]);
  }
  printf("\n");
  return 0;
}