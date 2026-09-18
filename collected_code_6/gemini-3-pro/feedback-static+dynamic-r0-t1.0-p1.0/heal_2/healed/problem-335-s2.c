#include <stdio.h>
#include <stdlib.h>

long long sum_of_ap(long long n, long long a, long long d) {
    if (n <= 0) {
        return 0;
    }
    
    unsigned long long un = (unsigned long long)n;
    unsigned long long ua = (unsigned long long)a;
    unsigned long long ud = (unsigned long long)d;
    unsigned long long sum;

    if (un % 2 == 0) {
        sum = (un / 2) * (2 * ua + (un - 1) * ud);
    } else {
        sum = un * (ua + ((un - 1) / 2) * ud);
    }
    
    return (long long)sum;
}

int main(void) {
    long long n;
    long long a;
    long long d;
    long long sum;

    if (scanf("%lld %lld %lld", &n, &a, &d) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number of terms cannot be negative\n");
        return EXIT_FAILURE;
    }

    sum = sum_of_ap(n, a, d);

    printf("%lld\n", sum);

    return EXIT_SUCCESS;
}