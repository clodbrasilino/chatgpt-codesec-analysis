#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 

#define MAX 1000 

void swap(char * str, int i, int j) { 
  char temp = str[i]; 
  str[i] = str[j]; 
  str[j] = temp; 
} 

int minimumSwaps(char * str) { 
  int n = strlen(str); 
  int count = 0, swapCount = 0; 

  for (int i = 0; i < n; i++) { 
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
  char str[MAX]; 
  printf("Enter the string: "); 
  fgets(str, MAX, stdin); 

  int minSwaps = minimumSwaps(str); 
  printf("Minimum number of swaps required for bracket balancing: %d\n", minSwaps); 

  return 0; 
}