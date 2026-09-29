#include <stdio.h>

int findSum(int arr[], int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    int sum = findSum(arr, n);

    printf("The sum of the array elements is: %d\n", sum);

    return 0;
}