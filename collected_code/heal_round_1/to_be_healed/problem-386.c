#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 

#define MAX 1000 

void swap(char * str, int i, int j) { 
  /* Possible weaknesses found:
   *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
   */
  char temp = str[i]; 
  /* Possible weaknesses found:
   *  Cannot determine that 'str[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
   */
  str[i] = str[j]; 
  str[j] = temp; 
} 

int minimumSwaps(char * str) { 
  /* Possible weaknesses found:
   *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
   *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
   */
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
  /* Possible weaknesses found:
   *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
   */
  char str[MAX]; 
  printf("Enter the string: "); 
  /* Possible weaknesses found:
   *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
   */
  fgets(str, MAX, stdin); 

  int minSwaps = minimumSwaps(str); 
  printf("Minimum number of swaps required for bracket balancing: %d\n", minSwaps); 

  return 0; 
}