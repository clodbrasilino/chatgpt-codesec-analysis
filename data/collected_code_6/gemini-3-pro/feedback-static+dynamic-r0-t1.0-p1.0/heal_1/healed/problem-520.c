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

long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return (a / gcd(a, b)) * b;
}

long long findArrayLcm(const long long *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }
    
    long long result = arr[0];
    for (size_t i = 1; i < size; i++) {
        result = lcm(result, arr[i]);
    }
    
    return result;
}

int main(void) {
    long long arr[] = {12, 15, 75};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    long long result = findArrayLcm(arr, size);
    
    printf("%lld\n", result);
    
    return 0;
}