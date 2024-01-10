#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int power(int base, int exponent) {
  return pow(base, exponent);
}

void createPowerList(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'arr' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    arr[i] = power(i, i);
  }
}

int main() {
  int size;
  printf("Enter the size of the list: ");
  /* Possible weaknesses found:
   *  Cannot determine that 'size' is initialized [premium-bughuntingUninit]
   */
  scanf("%d", &size);
  
  int* powerList = (int*) malloc(size * sizeof(int));
  
  createPowerList(powerList, size);
  
  printf("The list of powers is:\n");
  for (int i = 0; i < size; i++) {
    /* Possible weaknesses found:
     *  Cannot determine that 'powerList[i]' is initialized [premium-bughuntingUninit]
     */
    printf("%d\n", powerList[i]);
  }
  
  /* Possible weaknesses found:
   *  Cannot determine that 'powerList[0]' is initialized [premium-bughuntingUninit]
   */
  free(powerList);
  
  return 0;
}