#include <stdio.h>

int findMinElements(const int arr[], int n, int k) {
    int count = 0;
    int min = arr[0];
    int max = arr[0];
  
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        } else if (arr[i] > max) {
            max = arr[i];
        }
    }
  
    if (max - min > k) {
        for (int i = 0; i < n; i++) {
            if (arr[i] != min && arr[i] != max) {
                count++;
            }
        }
    }
  
    return count;
}

int main() {
    int arr[] = {5, 6, 8, 2, 4, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    int result = findMinElements(arr, n, k);
  
    printf("Minimum number of elements to remove: %d\n", result);

    return 0;
}