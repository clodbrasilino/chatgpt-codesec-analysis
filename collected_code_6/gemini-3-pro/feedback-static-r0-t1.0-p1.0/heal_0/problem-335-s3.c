#include <stdio.h>
#include <stdlib.h>

long long int arithmetic_progression_sum(int a, int d, int n) {
    if (n <= 0) {
        return 0;
    }
    return (long long int)n * (2LL * a + (n - 1LL) * d) / 2LL;
}

int main(void) {
    int a = 2;
    int d = 3;
    int n = 5;

    long long int sum = arithmetic_progression_sum(a, d, n);
    printf("%lld\n", sum);

    return EXIT_SUCCESS;
}