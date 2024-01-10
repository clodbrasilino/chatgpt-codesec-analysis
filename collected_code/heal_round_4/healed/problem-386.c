#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 1000

void swap(char * const str, const int i, const int j) {
  char temp = str[i];
  str[i] = str[j];
  str[j] = temp;
}

int minimumSwaps(char * const str) {
  if(str == NULL)
    return -1;

  size_t n = strnlen(str, MAX);

  if(n >= MAX)
    exit(EXIT_FAILURE);

  int count = 0, swapCount = 0;

  for (size_t i = 0; i < n; i++) {
    if (str[i] == '[') {
      count++;
    } 
    else if (str[i] == ']' && count > 0) {
      count--;
    } 
    else if (str[i] == ']' && count == 0) {
      swapCount++;
    }
  }

  return swapCount;
}

int main() {
  char str[MAX] = {0};
  printf("Enter the string: ");
  if(NULL == fgets(str, sizeof(str) - 1, stdin)) {
    exit(EXIT_FAILURE);
  }

  str[strnlen(str, sizeof(str) - 1) - 1] = '\0'; 

  const int MIN_SWAP = minimumSwaps(str);

  if(MIN_SWAP != -1) {
    printf("Minimum number of swaps required for bracket balancing: %d\n", MIN_SWAP);
  } 
  else {
    printf("Error: minimumSwaps function encountered a problem\n");
  }

  return 0;
}