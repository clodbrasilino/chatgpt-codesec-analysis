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

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int array_lcm(const int *arr, int n) {
    int result = 1;
    for (int i = 0; i < n; ++i) {
        result = lcm(result, arr[i]);
    }
    return result;
}

int main() {
    int arr[] = {2, 7, 3, 9, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("LCM of array elements is: %d\n", array_lcm(arr, n));
    return 0;
}