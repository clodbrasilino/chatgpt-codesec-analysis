#include <stdio.h>

int countIntegers(int arr[], int n) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        count++;
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int count = countIntegers(arr, n);
    printf("Number of integers in the array: %d\n", count);
    return 0;
}