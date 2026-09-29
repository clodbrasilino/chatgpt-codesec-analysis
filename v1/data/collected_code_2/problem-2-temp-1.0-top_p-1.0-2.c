#include <stdio.h>
#include <stdlib.h>

void find_similar_elements(int arr1[], int arr2[], int n1, int n2) {
    int i, j;
    for(i = 0; i < n1; i++) {
        for(j = 0; j< n2; j++) {
            if(arr1[i] == arr2[j]) {
                printf("%d ", arr1[i]);
            }
        }
    }
}

int main() {
  int arr1[] = {1, 3, 2, 7, 8, 9};
  int arr2[] = {2, 7, 1, 10, 11, 0};

  int n1 = sizeof(arr1) / sizeof(arr1[0]);
  int n2 = sizeof(arr2) / sizeof(arr2[0]);

  find_similar_elements(arr1, arr2, n1, n2);

  return 0;
}