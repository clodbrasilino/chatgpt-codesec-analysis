#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_perrin_numbers(size_t count, uint64_t *sum)
{
    uint64_t p0 = 3;
    uint64_t p1 = 0;
    uint64_t p2 = 2;
    uint64_t total = 0;

    if (sum == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        uint64_t current;

        if (i == 0) {
            current = p0;
        } else if (i == 1) {
            current = p1;
        } else if (i == 2) {
            current = p2;
        } else {
            if (UINT64_MAX - p0 < p1) {
                return -1;
            }

            current = p0 + p1;
            p0 = p1;
            p1 = p2;
            p2 = current;
        }

        if (UINT64_MAX - total < current) {
            return -1;
        }

        total += current;
    }

    *sum = total;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed_count;
    uint64_t sum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <count>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_count = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed_count > SIZE_MAX) {
        fputs("Invalid count\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_perrin_numbers((size_t)parsed_count, &sum) != 0) {
        fputs("Arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}