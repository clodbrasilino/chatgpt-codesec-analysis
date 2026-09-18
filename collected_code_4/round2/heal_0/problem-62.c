#include <stdio.h>

int findSmallestNumber(int arr[], int n) {
    int i;
    int smallest = arr[0];

    for (i = 0; i < n; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    return smallest;
}

int main() {
    int arr[] = {12, 23, 34, 5, 63, 21, 72};
    int n = sizeof(arr) / sizeof(arr[0]);
    int smallest = findSmallestNumber(arr, n);
    printf("Smallest number in the given array is %d", smallest);
    return 0;
}