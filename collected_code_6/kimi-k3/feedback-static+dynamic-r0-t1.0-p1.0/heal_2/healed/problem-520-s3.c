#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    long long g = gcd(a, b);
    if (a > LLONG_MAX / b || a < LLONG_MIN / b) {
        return -1;
    }
    return (a / g) * b;
}

long long findLCM(const long long arr[], int n) {
    long long result = arr[0];
    for (int i = 1; i < n; i++) {
        result = lcm(result, arr[i]);
        if (result == -1) return -1;
    }
    return result;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    if ((size_t)n > SIZE_MAX / sizeof(long long)) {
        printf("Memory allocation failed\n");
        return 1;
    }
    long long *arr = (long long *)malloc((size_t)n * sizeof(long long));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &arr[i]) != 1) {
            printf("Invalid input\n");
            free(arr);
            return 1;
        }
    }
    long long result = findLCM(arr, n);
    if (result == -1) {
        printf("LCM calculation overflowed\n");
    } else {
        printf("LCM of the given array elements is: %lld\n", result);
    }
    free(arr);
    return 0;
}