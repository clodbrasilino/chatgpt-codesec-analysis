#include <stdio.h>

void findPairs(const int arr[], int size, int target) {
    for (int i = 0; i < size-1; i++) {
        for (int j = i+1; j < size; j++) {
            if (arr[i] + arr[j] == target) {
                printf("(%d, %d)\n", arr[i], arr[j]);
            }
        }
    }
}

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  int size = sizeof(arr)/sizeof(arr[0]);
  int target = 7;
  findPairs(arr, size, target);
  
  return 0;
}