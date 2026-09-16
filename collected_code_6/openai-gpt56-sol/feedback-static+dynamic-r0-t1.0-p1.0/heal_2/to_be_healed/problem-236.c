#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_triangles(uint64_t side, uint64_t *result)
{
    if (result == NULL || side == 0) {
        return 0;
    }

    if (side > (UINT64_MAX - 1U) / 2U) {
        return 0;
    }

    uint64_t factor = side * 2U + 1U;

    if ((side & UINT64_C(1)) == 0U) {
        side /= 2U;
    } else {
        factor /= 2U;
    }

    if (side > UINT64_MAX / factor) {
        return 0;
    }

    *result = side * factor;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT64_MAX) {
        fprintf(stderr, "Invalid side length\n");
        return EXIT_FAILURE;
    }

    uint64_t result;

    if (!count_triangles((uint64_t)input, &result)) {
        fprintf(stderr, "Result cannot be represented\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}