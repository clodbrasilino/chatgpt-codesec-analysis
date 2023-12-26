#include <stdio.h>

void find_common_elements(int arr1[], int arr2[], int m, int n) {
  for(int i=0; i < m; i++) {
    for(int j=0; j < n; j++) {
      if(arr1[i] == arr2[j]) {
        printf("%d ", arr1[i]);
        break;
      }
    }
  }
}

int main() {
  int arr1[] = {10, 15, 20, 25, 30, 35};
  int arr2[] = {25, 30, 35, 40, 45};
  int m = sizeof(arr1)/sizeof(arr1[0]);
  int n = sizeof(arr2)/sizeof(arr2[0]);

  printf("Common elements are: ");
  find_common_elements(arr1, arr2, m, n);
  return 0;
}