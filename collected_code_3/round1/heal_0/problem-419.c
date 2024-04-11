#include <stdio.h>
#include <math.h>

void sum_and_multiply(int arr[], int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        arr[i] = round(arr[i]);
        sum += arr[i];
    }
    printf("%d\n", sum * n);
}

int main() {
    int arr[] = {1.2, 2.3, 3.4, 4.5, 5.6};
    int n = sizeof(arr) / sizeof(arr[0]);
    sum_and_multiply(arr, n);
    return 0;
}