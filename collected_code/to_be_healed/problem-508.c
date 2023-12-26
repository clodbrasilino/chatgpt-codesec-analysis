#include <stdbool.h>

bool checkOrder(int list1[], int list2[], int size1, int size2) {
  int i = 0, j = 0;
  
  while (i < size1 && j < size2) {
    /* Possible weaknesses found:
     *  Cannot determine that 'list2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (list1[i] == list2[j]) {
      i++;
    }
    j++;
  }
  
  if (i == size1) {
    return true;
  } else {
    return false;
  }
}