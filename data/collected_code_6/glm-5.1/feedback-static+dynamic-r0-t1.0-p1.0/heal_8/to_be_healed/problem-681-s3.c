#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned long smallest_prime_divisor(unsigned long n) {
    if (n <= 1) {
        return 0;
    }
    if (n % 2 == 0) {
        return 2;
    }
    for (unsigned long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return i;
        }
    }
    return n;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        fflush(stdout);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || errno != 0) {
        fprintf(stderr, "Invalid input: not a valid positive integer\n");
        fflush(stdout);
        return EXIT_FAILURE;
    }
    if (val == 0) {
        fprintf(stderr, "Invalid input: not a valid positive integer\n");
        fflush(stdout);
        return EXIT_FAILURE;
    }
    unsigned long result = smallest_prime_divisor(val);
    if (result == 0) {
        printf("No prime divisor for %lu\n", val);
    } else {
        printf("%lu\n", result);
    }
    fflush(stdout);
    return EXIT_SUCCESS;
}