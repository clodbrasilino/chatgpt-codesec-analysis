#include <stdio.h>
#include <stdlib.h>

int findSmallestMissingNumber(int arr[], int n) {
    int i = 0;

    while (i < n) {
        int j = arr[i] - 1;

        if (arr[i] > 0 && arr[i] <= n && arr[i] != arr[j]) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        } else {
            i++;
        }
    }

    for (i = 0; i < n; i++) {
        if (arr[i] != i + 1) {
            return i + 1;
        }
    }

    return n + 1;
}

int main() {
    int arr[] = {3, 4, -1, 1};
    int n = sizeof(arr) / sizeof(int);
    
    int smallestMissingNumber = findSmallestMissingNumber(arr, n);
    printf("Smallest missing number is: %d\n", smallestMissingNumber);
    
    return 0;
}