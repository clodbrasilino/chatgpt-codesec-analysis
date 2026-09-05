#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_even_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }

    if (l < 1) {
        l = 1;
    }
    if (r < 1) {
        return 0;
    }

    if (l % 2 != 0) {
        l++;
    }
    
    if (l > r) {
        return 0;
    }

    unsigned long long n = ((r - l) / 2) + 1;
    unsigned long long first = (unsigned long long)l;
    
    return n * (first + n - 1);
}

int main(int argc, char * const * const argv) {
    long long l, r;

    if (argc == 3) {
        char *endptr_l = NULL;
        char *endptr_r = NULL;
        l = strtoll(argv[1], &endptr_l, 10);
        r = strtoll(argv[2], &endptr_r, 10);

        if (*endptr_l != '\0' || *endptr_r != '\0' || endptr_l == argv[1] || endptr_r == argv[2]) {
            return EXIT_FAILURE;
        }
    } else if (scanf("%lld %lld", &l, &r) != 2) {
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_even_natural_numbers(l, r);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}