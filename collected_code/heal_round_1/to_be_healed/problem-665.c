#include <stdio.h>

void shiftElement(int list[], int size) {
  /* Possible weaknesses found:
   *  Cannot determine that 'list[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
   */
  int temp = list[0];

  for (int i = 0; i < size - 1; i++) {
    /* Possible weaknesses found:
     *  Cannot determine that 'list[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    list[i] = list[i + 1];
  }

  list[size - 1] = temp;
}

int main() {
  int list[5] = {1, 2, 3, 4, 5};

  shiftElement(list, 5);

  for (int i = 0; i < 5; i++) {
    printf("%d ", list[i]);
  }

  return 0;
}