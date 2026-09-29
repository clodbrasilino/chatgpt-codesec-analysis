#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

    sieve = malloc(n);
    if (sieve == NULL) {
        return -1;
    }

    memset(sieve, 1, n);
    sieve[0] = 0;
    sieve[1] = 0;

    for (i = 2UL; i * i < n; i++) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoul(buffer, &endptr, 10);
    if (endptr == buffer || errno != 0) {
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