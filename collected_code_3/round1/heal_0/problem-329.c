#include <stdio.h>

int countNegativeNumbers(int arr[], int n) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] < 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = { -1, -2, 3, 4, -5, -6, 7, 8, 9, -10 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Number of negative numbers: %d", countNegativeNumbers(arr, n));
    return 0;
}