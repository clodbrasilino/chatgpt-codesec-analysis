#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int count_distinct_prime_powers(int n) {
    if (n <= 1) {
        return 0;
    }
    int count = 0;
    int original = n;
    for (int p = 2; p * p <= original; p++) {
        if (n % p == 0) {
            count++;
            while (n % p == 0) {
                n /= p;
            }
        }
    }
    if (n > 1) {
        count++;
    }
    return count;
}

int main(int argc, char * const * const argv) {
    int num;
    if (argc != 2) {
        char buffer[12];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return EXIT_FAILURE;
        }
        char *endptr;
        errno = 0;
        long val = strtol(buffer, &endptr, 10);
        if (errno != 0 || (*endptr != '\0' && *endptr != '\n') || val < 0 || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        num = (int)val;
    } else {
        char *endptr;
        errno = 0;
        long val = strtol(argv[1], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || val < 0 || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        num = (int)val;
    }
    printf("%d\n", count_distinct_prime_powers(num));
    return EXIT_SUCCESS;
}