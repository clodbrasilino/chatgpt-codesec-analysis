#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    long long l, r;
    char *endptr1, *endptr2;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <l> <r>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    l = strtoll(argv[1], &endptr1, 10);
    if (errno != 0 || *endptr1 != '\0' || endptr1 == argv[1]) {
        fprintf(stderr, "Invalid input for l\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    r = strtoll(argv[2], &endptr2, 10);
    if (errno != 0 || *endptr2 != '\0' || endptr2 == argv[2]) {
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