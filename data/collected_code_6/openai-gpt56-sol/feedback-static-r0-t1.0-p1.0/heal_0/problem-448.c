#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_perrin(size_t count, uint64_t *sum)
{
    uint64_t p0 = 3;
    uint64_t p1 = 0;
    uint64_t p2 = 2;
    uint64_t total = 0;

    if (sum == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        uint64_t current;
        uint64_t next;

        if (i == 0) {
            current = p0;
        } else if (i == 1) {
            current = p1;
        } else {
            current = p2;
        }

        if (UINT64_MAX - total < current) {
            return 0;
        }
        total += current;

        if (i >= 2 && i + 1 < count) {
            if (UINT64_MAX - p0 < p1) {
                return 0;
            }
            next = p0 + p1;
            p0 = p1;
            p1 = p2;
            p2 = next;
        }
    }

    *sum = total;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t sum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <count>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || input > SIZE_MAX) {
        fprintf(stderr, "Invalid count\n");
        return EXIT_FAILURE;
    }

    if (!sum_perrin((size_t)input, &sum)) {
        fprintf(stderr, "Arithmetic overflow\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}