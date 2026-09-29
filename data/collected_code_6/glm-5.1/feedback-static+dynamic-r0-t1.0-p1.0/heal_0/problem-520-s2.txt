#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm_array(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    long long result = 1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            return 0;
        }
        long long current = arr[i] < 0 ? -arr[i] : arr[i];
        if (current == 0) {
            return 0;
        }
        long long g = gcd(result, current);
        result = (result / g) * current;
    }
    return result;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    long long result = lcm_array(arr, n);
    printf("%lld\n", result);
    free(arr);
    return 0;
}