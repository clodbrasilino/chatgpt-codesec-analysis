#include <stdio.h>
#include <stdlib.h>

unsigned long find_nth_non_multiple(unsigned long n, unsigned long k) {
    if (k == 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        exit(EXIT_FAILURE);
    }
    unsigned long complete_sets = (n - 1) / (k - 1);
    unsigned long remainder = (n - 1) % (k - 1);
    return complete_sets * k + remainder + 1;
}

int main(void) {
    unsigned long n = 0;
    unsigned long k = 0;
    if (scanf("%lu %lu", &n, &k) != 2) {
        return EXIT_FAILURE;
    }
    if (n == 0 || k == 0) {
        return EXIT_FAILURE;
    }
    unsigned long result = find_nth_non_multiple(n, k);
    printf("%lu\n", result);
    return EXIT_SUCCESS;
}