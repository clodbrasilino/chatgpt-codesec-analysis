#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_perrin(uint64_t count, uint64_t *sum)
{
    uint64_t p0 = 3;
    uint64_t p1 = 0;
    uint64_t p2 = 2;
    uint64_t total = 0;

    if (sum == NULL) {
        return -1;
    }

    for (uint64_t i = 0; i < count; ++i) {
        uint64_t current;

        if (i == 0) {
            current = p0;
        } else if (i == 1) {
            current = p1;
        } else if (i == 2) {
            current = p2;
        } else {
            if (p0 > UINT64_MAX - p1) {
                return -1;
            }
            current = p0 + p1;
            p0 = p1;
            p1 = p2;
            p2 = current;
        }

        if (total > UINT64_MAX - current) {
            return -1;
        }
        total += current;
    }

    *sum = total;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed_count;
    uint64_t sum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_terms>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_count = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed_count > UINT64_MAX) {
        fprintf(stderr, "Invalid number of terms\n");
        return EXIT_FAILURE;
    }

    if (sum_perrin((uint64_t)parsed_count, &sum) != 0) {
        fprintf(stderr, "Arithmetic overflow\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}