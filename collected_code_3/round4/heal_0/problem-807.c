#include <stdio.h>

int findFirstOdd(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 != 0) {
            return arr[i];
        }
    }
    return -1;
}

int main() {
    int arr[] = {2, 4, 6, 8, 10, 11, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int firstOdd = findFirstOdd(arr, n);
    if(firstOdd != -1) {
        printf("First odd number in the array is: %d", firstOdd);
    } else {
        printf("No odd number found in the array.");
    }
    return 0;
}