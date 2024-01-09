#include <stdio.h>
int findDifference(int list[], int size) {
  int even = -1;
  int odd = -1;
  
  for (int i = 0; i < size; i++) {
    if (list[i] % 2 == 0 && even == -1) {
      even = list[i];
      continue;
    }
    if (list[i] % 2 != 0 && odd == -1) {
      odd = list[i];
      continue;
    }
    if (even != -1 && odd != -1) {
      break;
    }
  }
  
  if (even == -1 || odd == -1) {
    return -1;
  }
  
  return even - odd;
}