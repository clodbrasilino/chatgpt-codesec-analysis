#include <stdio.h>
#include <limits.h>

int findSmallestMissingNumber(int arr[], int n) {
    int min = INT_MAX;
    int count[100] = {0};

    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] < 100 && arr[i] >= 0) {
            count[arr[i]]++;
        }
    }

    for (int i = 0; i < 100; i++) {
        if (count[i] == 0 && i >= min) {
            return i;
        } 
    }

    return 100;
}

int main() {
    int arr[] = {0, 1, 2, 6, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int missingNumber = findSmallestMissingNumber(arr, n);
  
    printf("Smallest missing number is: %d", missingNumber);
  
    return 0;
}