#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long long sum_of_fourth_powers_of_odd_numbers(int n) {
    if (n <= 0) {
        return 0;
    }

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long odd = 2LL * i + 1;
        long long odd2, odd4;
        
        if (__builtin_mul_overflow(odd, odd, &odd2)) return -1;
        if (__builtin_mul_overflow(odd2, odd2, &odd4)) return -1;
        if (__builtin_add_overflow(sum, odd4, &sum)) return -1;
    }

    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return EXIT_FAILURE;
    }

    long long result = sum_of_fourth_powers_of_odd_numbers(n);
    if (result == -1) {
        fprintf(stderr, "Integer overflow detected\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}