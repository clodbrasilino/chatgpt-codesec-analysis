#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long centered_hexagonal(unsigned int n) {
    return 1ULL + (unsigned long long)n * (n - 1) * 3;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || errno == ERANGE || val == 0 || val > UINT_MAX) {
        fprintf(stderr, "Invalid input. n must be a positive integer within unsigned int range.\n");
        return 1;
    }

    unsigned int n = (unsigned int)val;
    unsigned long long result = centered_hexagonal(n);

    printf("%llu\n", result);
    return 0;
}