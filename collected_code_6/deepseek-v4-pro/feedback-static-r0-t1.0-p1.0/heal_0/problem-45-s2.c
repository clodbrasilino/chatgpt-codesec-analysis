#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int array_gcd(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }
    int result = arr[0];
    for (size_t i = 1; i < n; ++i) {
        result = gcd(result, arr[i]);
        if (result == 1) {
            break;
        }
    }
    return result;
}

int main(void) {
    int arr[] = {24, 36, 48, 60};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int result = array_gcd(arr, n);
    printf("GCD: %d\n", result);
    return 0;
}