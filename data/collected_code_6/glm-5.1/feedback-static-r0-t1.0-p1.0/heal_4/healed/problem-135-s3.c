#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long hexagonal_number(unsigned long long n) {
    return n * (2 * n - 1);
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long long n = strtoull(argv[1], &endptr, 10);

    if (errno == ERANGE || *endptr != '\0' || argv[1][0] == '-' || n == 0) {
        fprintf(stderr, "Error: Invalid input. n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned long long max_n = 3037000499ULL;
    if (n > max_n || (max_n > 0 && hexagonal_number(max_n) / max_n < 2 * max_n - 1)) {
        if (n > max_n) {
            fprintf(stderr, "Error: Input too large. Risk of unsigned long long overflow.\n");
            return EXIT_FAILURE;
        }
    }

    unsigned long long result = hexagonal_number(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}