#include <stdio.h>
#include <stdlib.h>

unsigned long long count_squares(unsigned int m, unsigned int n) {
    unsigned long long count = 0;
    while (m > 0 && n > 0) {
        count += (unsigned long long)m * n;
        m--;
        n--;
    }
    return count;
}

int main(void) {
    unsigned int m;
    unsigned int n;

    if (scanf("%u %u", &m, &n) != 2) {
        return EXIT_FAILURE;
    }

    unsigned long long total_squares = count_squares(m, n);
    printf("%llu\n", total_squares);

    return EXIT_SUCCESS;
}