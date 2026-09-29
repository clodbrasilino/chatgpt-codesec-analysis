#include <stdio.h>

int minListLength(int* lists[], int numLists) {
  int minLength = -1;
  int minIndex = -1;

  for(int i = 0; i < numLists; i++) {
    /* Possible weaknesses found:
     *  Cannot determine that 'lists[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  implicit declaration of function 'findLength'; did you mean 'minListLength'? [-Wimplicit-function-declaration]
     */
    int length = findLength(lists[i]);
    if(minLength == -1 || length < minLength) {
      minLength = length;
      minIndex = i;
    }
  }
  
  if(minIndex != -1) {
    return minIndex;
  }
  else {
    return -1; // no list found
  }
}

int findLength(int* list) {
  int length = 0;
  
  /* Possible weaknesses found:
   *  Cannot determine that 'list[length]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
   */
  while(list[length] != '\0') {
    length++;
  }
  
  return length;
}