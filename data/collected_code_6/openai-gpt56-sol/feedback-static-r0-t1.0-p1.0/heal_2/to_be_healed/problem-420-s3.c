#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum_even(uint64_t n, uint64_t *result)
{
    uint64_t triangular;

    if (result == NULL || n > UINT64_C(65535)) {
        return -1;
    }

    triangular = n * (n + UINT64_C(1)) / UINT64_C(2);
    *result = UINT64_C(8) * triangular * triangular;

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (cube_sum_even((uint64_t)input, &result) != 0) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}