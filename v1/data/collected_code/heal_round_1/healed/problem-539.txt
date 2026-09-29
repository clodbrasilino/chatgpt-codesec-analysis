#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int power(int base, int exponent) {
  return (int) pow(base, exponent);
}

void createPowerList(int* arr, int size) {
  if (arr == NULL) {
      printf("Memory not allocated.\n");
      exit(0);
  }

  for (int i = 0; i < size; i++) {
    arr[i] = power(i, i);
  }
}

int main() {
  int size = 0;
  printf("Enter the size of the list: ");
  scanf("%d", &size);
  
  if(size <= 0){
      printf("Invalid input.\n");
      return -1;
  }

  int* powerList = (int*) malloc(size * sizeof(int));

  if (powerList == NULL){
      printf("Memory not allocated.\n");
      return -1;
  }
  
  createPowerList(powerList, size);
  
  printf("The list of powers is:\n");
  for (int i = 0; i < size; i++) {
    printf("%d\n", powerList[i]);
  }
  
  free(powerList);

  return 0;
}
