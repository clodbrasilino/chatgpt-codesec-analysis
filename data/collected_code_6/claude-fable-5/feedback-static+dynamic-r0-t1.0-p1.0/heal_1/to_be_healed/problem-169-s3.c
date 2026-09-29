#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

static int pell(unsigned int n, unsigned long long *result)
{
    unsigned long long prev;
    unsigned long long curr;
    /* Possible weaknesses found:
     *  The scope of the variable 'next' can be reduced. [variableScope]
     */
    unsigned long long next;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    if (n == 0U) {
        *result = 0ULL;
        return 0;
    }

    if (n == 1U) {
        *result = 1ULL;
        return 0;
    }

    prev = 0ULL;
    curr = 1ULL;

    for (i = 2U; i <= n; i++) {
        if (curr > (ULLONG_MAX - prev) / 2ULL) {
            return -1;
        }
        next = (2ULL * curr) + prev;
        prev = curr;
        curr = next;
    }

    *result = curr;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *endptr;
    long value;
    unsigned long long pell_result;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    endptr = NULL;
    value = strtol(argv[1], &endptr, 10);

    if (errno != 0) {
        (void)fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (endptr == argv[1] || *endptr != '\0') {
        (void)fprintf(stderr, "Error: input is not a valid integer\n");
        return EXIT_FAILURE;
    }

    if (value < 0L || value > (long)UINT_MAX) {
        (void)fprintf(stderr, "Error: input out of range\n");
        return EXIT_FAILURE;
    }

    if (pell((unsigned int)value, &pell_result) != 0) {
        (void)fprintf(stderr, "Error: result overflows\n");
        return EXIT_FAILURE;
    }

    if (printf("Pell(%ld) = %llu\n", value, pell_result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}