#include <stdio.h>
#include <stdlib.h>

unsigned long long count_squares(unsigned int m, unsigned int n);

unsigned long long count_squares(unsigned int m, unsigned int n) {
    unsigned long long count = 0;
    unsigned int k;
    unsigned int min_dim = (m < n) ? m : n;

    for (k = 1; k <= min_dim; ++k) {
        count += (unsigned long long)(m - k + 1) * (n - k + 1);
    }

    return count;
}

int main(void) {
    unsigned int m = 0;
    unsigned int n = 0;
    int result;

    result = scanf("%u %u", &m, &n);

    if (result != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", count_squares(m, n));

    return EXIT_SUCCESS;
}