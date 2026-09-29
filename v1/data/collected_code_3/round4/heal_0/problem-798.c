#include <stdio.h>

int arraySum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = arraySum(arr, n);
    printf("Sum of array is %d\n", sum);
    return 0;
}