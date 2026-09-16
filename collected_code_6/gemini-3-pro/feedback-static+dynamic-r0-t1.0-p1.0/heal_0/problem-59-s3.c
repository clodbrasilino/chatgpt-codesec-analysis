#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int get_nth_octagonal(unsigned int n, unsigned long long *result) {
    unsigned long long n_ull;
    unsigned long long term;

    if (n == 0 || result == NULL) {
        return -1;
    }

    n_ull = (unsigned long long)n;
    term = (3ULL * n_ull) - 2ULL;

    if (n_ull > 0ULL && term > (ULLONG_MAX / n_ull)) {
        return -1;
    }

    *result = n_ull * term;
    return 0;
}

int main(void) {
    unsigned int n = 10;
    unsigned long long octagonal_number = 0;
    int status;

    status = get_nth_octagonal(n, &octagonal_number);

    if (status == 0) {
        printf("%llu\n", octagonal_number);
    } else {
        fprintf(stderr, "Error computing the octagonal number.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}