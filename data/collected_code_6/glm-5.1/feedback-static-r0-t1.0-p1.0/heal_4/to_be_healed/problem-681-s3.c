#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

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
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    if (argv[1][0] == '\0') {
        fprintf(stderr, "Invalid input: empty string\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    
    if (errno == ERANGE || val > ULONG_MAX) {
        fprintf(stderr, "Invalid input: value out of range\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(argv[1]) != (size_t)(endptr - argv[1])) {
        fprintf(stderr, "Invalid input: not a valid positive integer\n");
        return EXIT_FAILURE;
    }
    
    unsigned long result = smallest_prime_divisor(val);
    if (result == 0) {
        printf("No prime divisor for %lu\n", val);
    } else {
        printf("%lu\n", result);
    }
    return EXIT_SUCCESS;
}