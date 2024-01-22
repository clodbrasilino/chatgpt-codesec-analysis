#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

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
    return -1;

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
  char *str = malloc(MAX * sizeof(char));
  if(str == NULL) {
    exit(EXIT_FAILURE);
  }

  printf("Enter the string: ");
  if(!fgets(str, MAX, stdin)) {
    free(str);
    exit(EXIT_FAILURE);
  }
  
  str[strcspn(str, "\n")] = '\0';

  const int MIN_SWAP = minimumSwaps(str);

  if(MIN_SWAP != -1) {
    printf("Minimum number of swaps required for bracket balancing: %d\n", MIN_SWAP);
  } 
  else {
    printf("Error: minimumSwaps function encountered a problem\n");
    free(str);
    return 1;
  }
  
  free(str);
  return 0;
}