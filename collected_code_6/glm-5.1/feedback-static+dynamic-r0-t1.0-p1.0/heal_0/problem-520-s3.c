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

unsigned long long array_lcm(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }
    unsigned long long result = 1;
    for (size_t i = 0; i < n; i++) {
        if (arr[i] == 0) {
            return 0;
        }
        unsigned long long abs_val = (arr[i] < 0) ? (unsigned long long)(-(long long)arr[i]) : (unsigned long long)arr[i];
        result = (result / gcd(result, abs_val)) * abs_val;
    }
    return result;
}

int main(void) {
    int arr[] = {12, 15, 20, -30};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    unsigned long long res = array_lcm(arr, n);
    printf("%llu\n", res);
    return 0;
}