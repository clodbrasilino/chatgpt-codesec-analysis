#include <stdio.h>
#include <stdlib.h>

unsigned long long* compute_delannoy(int n) {
    if (n < 0) {
        return NULL;
    }

    unsigned long long *d = malloc(((size_t)n + 1) * sizeof(unsigned long long));
    if (!d) {
        return NULL;
    }

    d[0] = 1ULL;

    for (int i = 1; i <= n; ++i) {
        unsigned long long prev = 1ULL;
        for (int j = 1; j <= i; ++j) {
            unsigned long long temp = d[j];
            d[j] = d[j] + d[j - 1] + prev;
            prev = temp;
        }
    }

    return d;
}

int main(int argc, char * const * const argv) {
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    if (sscanf(argv[1], "%d", &n) != 1) {
        fprintf(stderr, "Invalid integer input\n");
        return 1;
    }

    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return 1;
    }

    unsigned long long *d = compute_delannoy(n);
    if (!d) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%llu\n", d[n]);

    free(d);
    d = NULL;

    return 0;
}