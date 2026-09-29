#include <stdio.h>

int findMaxOccurrence(int* list, int size) {
  int maxCount = 0, maxValue = 0;
  
  for(int i = 0; i < size; i++) {
    int count = 0;
    
    for(int j = 0; j < size; j++) {
      /* Possible weaknesses found:
       *  Cannot determine that 'list[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      if(list[j] == list[i])
        count++;
    }
    
    if(count > maxCount) {
      maxCount = count;
      /* Possible weaknesses found:
       *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      maxValue = list[i];
    }
  }
  
  return maxValue;
}

int main() {
  int list[] = {1, 2, 2, 3, 3, 3, 4, 5, 5, 5, 5};
  int size = sizeof(list) / sizeof(list[0]);
  
  int max = findMaxOccurrence(list, size);
  printf("Item with maximum occurrences: %d\n", max);
  
  return 0;
}