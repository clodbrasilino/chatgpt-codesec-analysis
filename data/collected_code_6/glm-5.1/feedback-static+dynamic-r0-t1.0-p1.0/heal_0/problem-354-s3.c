#include <stdio.h>
#include <stdlib.h>

long long find_arithmetic_term(int n, long long a, long long d) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }
    return a + (long long)(n - 1) * d;
}

int main(void) {
    int n;
    long long a, d, term;

    if (scanf("%d %lld %lld", &n, &a, &d) != 3) {
        return EXIT_FAILURE;
    }

    term = find_arithmetic_term(n, a, d);

    printf("%lld\n", term);

    return EXIT_SUCCESS;
}