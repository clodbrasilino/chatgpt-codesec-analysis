#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int hamming_distance(uint64_t a, uint64_t b)
{
    uint64_t value = a ^ b;
    unsigned int distance = 0U;

    while (value != UINT64_C(0)) {
        distance += (unsigned int)(value & UINT64_C(1));
        value >>= 1U;
    }

    return distance;
}

static int sum_consecutive_hamming_distances(uint64_t o, uint64_t n,
                                             uint64_t *sum)
{
    uint64_t current;
    uint64_t total = UINT64_C(0);

    if (sum == NULL || o > n) {
        return 0;
    }

    for (current = o; current < n; ++current) {
        const unsigned int distance =
            hamming_distance(current, current + UINT64_C(1));

        if (UINT64_MAX - total < (uint64_t)distance) {
            return 0;
        }

        total += (uint64_t)distance;
    }

    *sum = total;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(int argc, char *const argv[])
{
    uint64_t o;
    uint64_t n;
    uint64_t sum;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <o> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &o) || !parse_uint64(argv[2], &n)) {
        fprintf(stderr,
                "Both arguments must be valid unsigned 64-bit integers.\n");
        return EXIT_FAILURE;
    }

    if (!sum_consecutive_hamming_distances(o, n, &sum)) {
        fprintf(stderr, "Invalid range or arithmetic overflow.\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}