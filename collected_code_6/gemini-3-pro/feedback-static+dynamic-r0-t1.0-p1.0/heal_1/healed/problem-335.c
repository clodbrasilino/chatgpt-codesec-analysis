#include <stdio.h>
#include <stdlib.h>

long long sum_of_arithmetic_progression(long long a, long long d, long long n) {
    if (n <= 0) {
        return 0;
    }

    unsigned long long ua = (unsigned long long)a;
    unsigned long long ud = (unsigned long long)d;
    unsigned long long un = (unsigned long long)n;
    unsigned long long result;

    if (un % 2 == 0) {
        result = (un / 2) * ((2ULL * ua) + (un - 1ULL) * ud);
    } else {
        result = un * (ua + ((un - 1ULL) / 2) * ud);
    }

    return (long long)result;
}

int main(void) {
    long long a = 0;
    long long d = 0;
    long long n = 0;
    long long sum = 0;
    int result = 0;

    result = scanf("%lld %lld %lld", &a, &d, &n);
    if (result != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number of terms cannot be negative\n");
        return EXIT_FAILURE;
    }

    sum = sum_of_arithmetic_progression(a, d, n);
    
    printf("%lld\n", sum);

    return EXIT_SUCCESS;
}