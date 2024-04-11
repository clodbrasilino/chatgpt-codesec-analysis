#include <stdio.h>
#include <math.h>

void sum_and_multiply(int arr[], int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        arr[i] = round(arr[i]);
        sum += arr[i];
    }
    int result = sum * n;
    printf("%d\n", result);
}

int main() {
    int arr[] = {1.2, 2.8, 3.5, 4.7, 5.3};
    int n = sizeof(arr) / sizeof(arr[0]);
    sum_and_multiply(arr, n);
    return 0;
}