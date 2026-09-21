#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long centered_hexagonal(unsigned int n) {
    unsigned long long term = n;
    return 3 * term * (term - 1) + 1;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long long val = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0' || val == 0 || val > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    
    char buf[32];
    int len = snprintf(buf, sizeof(buf), "%llu\n", centered_hexangular(n));
    if (len < 0 || len >= (int)sizeof(buf)) {
        return EXIT_FAILURE;
    }
    fputs(buf, stdout);

    return EXIT_SUCCESS;
}