#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int count_primes(unsigned long n, unsigned long *result)
{
    unsigned char *sieve;
    unsigned long i;
    unsigned long j;
    unsigned long count;

    if (result == NULL) {
        return -1;
    }

    if (n < 3UL) {
        *result = 0UL;
        return 0;
    }

    if (n > (unsigned long)(SIZE_MAX < ULONG_MAX ? SIZE_MAX : ULONG_MAX)) {
        return -1;
    }

    sieve = malloc((size_t)n);
    if (sieve == NULL) {
        return -1;
    }

    memset(sieve, 1, (size_t)n);
    sieve[0] = 0;
    sieve[1] = 0;

    for (i = 2UL; i <= (n - 1UL) / i; i++) {
        if (sieve[i] == 1) {
            for (j = i * i; j < n; j += i) {
                sieve[j] = 0;
            }
        }
    }

    count = 0UL;
    for (i = 2UL; i < n; i++) {
        if (sieve[i] == 1) {
            count++;
        }
    }

    free(sieve);
    *result = count;
    return 0;
}

int main(void)
{
    unsigned long n;
    unsigned long result;
    char buffer[64];
    char *endptr;
    size_t len;
    const char *p;

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    p = buffer;
    while (isspace((unsigned char)*p)) {
        p++;
    }
    if (*p == '-') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoul(buffer, &endptr, 10);
    if (endptr == buffer || errno != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (count_primes(n, &result) != 0) {
        fprintf(stderr, "Failed to count primes\n");
        return EXIT_FAILURE;
    }

    printf("%lu\n", result);
    return EXIT_SUCCESS;
}