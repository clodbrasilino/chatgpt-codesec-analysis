#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_positive_sequence(int64_t n, int64_t *result)
{
    if (result == NULL || n <= 0) {
        return 0;
    }

    uint64_t terms = ((uint64_t)n + 1U) / 2U;

    if ((n & 1) == 0) {
        *result = (int64_t)(terms * (terms + 1U));
    } else {
        *result = (int64_t)(terms * terms);
    }

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    int64_t n;
    int64_t sum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoimax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0') {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    if (!sum_positive_sequence(n, &sum)) {
        fprintf(stderr, "Input must be a positive integer\n");
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", sum);
    return EXIT_SUCCESS;
}