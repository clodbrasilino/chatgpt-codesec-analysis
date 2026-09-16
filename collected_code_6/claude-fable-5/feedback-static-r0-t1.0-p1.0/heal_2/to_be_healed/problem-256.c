#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

static int count_primes(unsigned int n, unsigned int *result)
{
    unsigned char *sieve = NULL;
    unsigned int count = 0;
    unsigned int i;
    unsigned int j;

    if (result == NULL) {
        return -1;
    }

    if (n < 3U) {
        *result = 0U;
        return 0;
    }

    sieve = calloc((size_t)n, sizeof(unsigned char));
    if (sieve == NULL) {
        return -1;
    }

    for (i = 2U; i < n; i++) {
        if (sieve[i] == 0U) {
            count++;
            if (i <= (n - 1U) / i) {
                for (j = i * i; j < n; j += i) {
                    sieve[j] = 1U;
                }
            }
        }
    }

    free(sieve);
    sieve = NULL;

    *result = count;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    unsigned long input;
    unsigned int n;
    unsigned int result = 0U;
    char *endptr = NULL;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <non-negative number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (input > (unsigned long)UINT_MAX) {
        (void)fprintf(stderr, "Input too large\n");
        return EXIT_FAILURE;
    }

    n = (unsigned int)input;

    if (count_primes(n, &result) != 0) {
        (void)fprintf(stderr, "Failed to count primes\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of primes less than %u: %u\n", n, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}