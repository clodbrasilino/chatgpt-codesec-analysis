#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tupleToList(char tuple[], char string[], char list[]) {
  int i, j;

  strcpy(list, "");

  for(i = 0; i < strlen(tuple); i++) {
    strncat(list, tuple + i, 1);
    strcat(list, string);
  }
}

int main() {
  char tuple[] = "12345";
  char string[] = "-";
  char list[50];

  tupleToList(tuple, string, list);

  printf("%s\n", list);

  return 0;
}