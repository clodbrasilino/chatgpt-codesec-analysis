#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long gcd_ll(long long a, long long b)
{
    if (a < 0) {
        if (a == LLONG_MIN) {
            return -1;
        }
        a = -a;
    }
    if (b < 0) {
        if (b == LLONG_MIN) {
            return -1;
        }
        b = -b;
    }
    
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm_ll(long long a, long long b, long long *result)
{
    if (a == 0 || b == 0) {
        *result = 0;
        return 0;
    }
    
    long long g = gcd_ll(a, b);
    if (g == -1 || g == 0) {
        return -1;
    }
    
    long long abs_a = (a < 0) ? -a : a;
    long long abs_b = (b < 0) ? -b : b;
    
    if (abs_a > LLONG_MAX / (abs_b / g)) {
        return -1;
    }
    
    *result = (abs_a / g) * abs_b;
    return 0;
}

int array_lcm(const long long *arr, size_t size, long long *result)
{
    if (arr == NULL || result == NULL || size == 0) {
        return -1;
    }
    
    long long lcm = 1;
    
    for (size_t i = 0; i < size; i++) {
        if (lcm_ll(lcm, arr[i], &lcm) != 0) {
            return -1;
        }
    }
    
    *result = lcm;
    return 0;
}

int main(void)
{
    long long arr[] = {12, 18, 24, 36};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    long long result;
    
    if (array_lcm(arr, size, &result) != 0) {
        fprintf(stderr, "Error: overflow or invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("LCM: %lld\n", result);
    return EXIT_SUCCESS;
}