#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

static int is_prime(unsigned long long n)
{
    unsigned long long i;

    if (n < 2ULL) {
        return 0;
    }
    if (n < 4ULL) {
        return 1;
    }
    if (n % 2ULL == 0ULL || n % 3ULL == 0ULL) {
        return 0;
    }
    for (i = 5ULL; i <= n / i; i += 6ULL) {
        if (n % i == 0ULL) {
            return 0;
        }
        if (i + 2ULL <= n / (i + 2ULL) || (i + 2ULL) * (i + 2ULL) <= n) {
            if (n % (i + 2ULL) == 0ULL) {
                return 0;
            }
        }
    }
    return 1;
}

static int nth_nsw_prime(unsigned int n, unsigned long long *result)
{
    unsigned long long s0;
    unsigned long long s1;
    /* Possible weaknesses found:
     *  The scope of the variable 'next' can be reduced. [variableScope]
     */
    unsigned long long next;
    unsigned int count;

    if (result == NULL || n == 0U) {
        return -1;
    }

    s0 = 1ULL;
    s1 = 1ULL;
    count = 0U;

    for (;;) {
        if (s1 > (ULLONG_MAX - s0) / 2ULL) {
            return -1;
        }
        next = 2ULL * s1 + s0;
        s0 = s1;
        s1 = next;
        if (is_prime(s1)) {
            count++;
            if (count == n) {
                *result = s1;
                return 0;
            }
        }
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    unsigned long parsed;
    unsigned long long prime;
    char *endptr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    endptr = NULL;
    parsed = strtoul(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (parsed == 0UL || parsed > UINT_MAX) {
        fprintf(stderr, "Input out of range: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (nth_nsw_prime((unsigned int)parsed, &prime) != 0) {
        fprintf(stderr, "Could not compute NSW prime %lu within 64-bit range\n", parsed);
        return EXIT_FAILURE;
    }

    if (printf("NSW prime %lu is %llu\n", parsed, prime) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}