#include <stdio.h>

float divideEvenOdd(int arr[], int n) {
    int even = 0, odd = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 == 0 && even == 0) {
            even = arr[i];
        }
        else if(arr[i] % 2 != 0 && odd == 0) {
            odd = arr[i];
        }
        if(even != 0 && odd != 0) {
            break;
        }
    }
    return (float)even / odd;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%f", divideEvenOdd(arr, n));
    return 0;
}