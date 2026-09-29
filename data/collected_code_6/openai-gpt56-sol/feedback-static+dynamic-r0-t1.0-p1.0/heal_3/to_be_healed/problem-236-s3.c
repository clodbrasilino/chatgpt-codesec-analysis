#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_equilateral_triangles(uint64_t n, uint64_t *result)
{
    __uint128_t count;

    if (result == NULL || n == 0) {
        return 0;
    }

    count = (__uint128_t)n * ((__uint128_t)n + 2U) *
            (2U * (__uint128_t)n + 1U);
    count /= 8U;

    if ((n & 1U) == 0U) {
        count -= (__uint128_t)n / 4U;
    }

    if (count > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)count;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t value;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <subdivisions>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        value == 0 || value > UINT64_MAX) {
        fprintf(stderr, "Invalid number of subdivisions\n");
        return EXIT_FAILURE;
    }

    if (!count_equilateral_triangles((uint64_t)value, &result)) {
        fprintf(stderr, "Result is out of range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}