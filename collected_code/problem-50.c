#include <stdio.h>

int minListLength(int* lists[], int numLists) {
  int minLength = -1;
  int minIndex = -1;

  for(int i = 0; i < numLists; i++) {
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
  
  while(list[length] != '\0') {
    length++;
  }
  
  return length;
}