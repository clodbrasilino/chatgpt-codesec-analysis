#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int power(int base, int exponent) {
  return pow(base, exponent);
}

void createPowerList(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    arr[i] = power(i, i);
  }
}

int main() {
  int size;
  printf("Enter the size of the list: ");
  scanf("%d", &size);
  
  int* powerList = (int*) malloc(size * sizeof(int));
  
  createPowerList(powerList, size);
  
  printf("The list of powers is:\n");
  for (int i = 0; i < size; i++) {
    printf("%d\n", powerList[i]);
  }
  
  free(powerList);
  
  return 0;
}