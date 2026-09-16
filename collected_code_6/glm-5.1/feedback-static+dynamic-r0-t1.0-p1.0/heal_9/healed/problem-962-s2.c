#include <stdio.h>
#include <stdlib.h>

long long sum_even_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }

    if (l <= 0) {
        l = 1;
    }

    if (l % 2 != 0) {
        l++;
    }

    if (r % 2 != 0) {
        r--;
    }

    if (l > r) {
        return 0;
    }

    long long count = ((r - l) / 2) + 1;
    return count * (l + r) / 2;
}

int main(int argc, char * const argv[const]) {
    long long l, r;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <l> <r>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%lld", &l) != 1) {
        fprintf(stderr, "Invalid input for l\n");
        return EXIT_FAILURE;
    }

    if (sscanf(argv[2], "%lld", &r) != 1) {
        fprintf(stderr, "Invalid input for r\n");
        return EXIT_FAILURE;
    }

    if (l < 0 || r < 0) {
        fprintf(stderr, "Inputs must be natural numbers\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", sum_even_natural_numbers(l, r));

    return EXIT_SUCCESS;
}