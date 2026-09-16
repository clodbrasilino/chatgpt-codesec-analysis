#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int findArrayGCD(int *arr, int n) {
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = gcd(result, arr[i]);
        if (result == 1) {
            break;
        }
    }
    return result;
}

int main() {
    int arr[] = {24, 36, 60, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findArrayGCD(arr, n);
    printf("GCD: %d\n", result);
    return 0;
}