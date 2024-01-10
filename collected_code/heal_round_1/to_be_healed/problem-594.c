#include <stdio.h>
int findDifference(int list[], int size) {
  int even = -1;
  int odd = -1;
  
  for (int i = 0; i < size; i++) {
    /* Possible weaknesses found:
     *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (list[i] % 2 == 0 && even == -1) {
      /* Possible weaknesses found:
       *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      even = list[i];
      continue;
    }
    /* Possible weaknesses found:
     *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (list[i] % 2 != 0 && odd == -1) {
      /* Possible weaknesses found:
       *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
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