#include <stdio.h>

int findDifference(int arr[], int n) {
    int firstEven = -1, firstOdd = -1;
    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 == 0 && firstEven == -1) {
            firstEven = arr[i];
        }
        if(arr[i] % 2 != 0 && firstOdd == -1) {
            firstOdd = arr[i];
        }
        if(firstEven != -1 && firstOdd != -1) {
            break;
        }
    }
    return firstEven - firstOdd;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d", findDifference(arr, n));
    return 0;
}