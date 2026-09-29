#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int lcm(int arr[], int n) {
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = (result * arr[i]) / gcd(result, arr[i]);
    }
    return result;
}

int main() {
    int arr[] = {2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("LCM of array elements: %d\n", lcm(arr, n));
    return 0;
}