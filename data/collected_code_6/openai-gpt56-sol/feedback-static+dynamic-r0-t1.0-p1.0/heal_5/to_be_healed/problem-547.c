#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t sum_consecutive_hamming_distances(uint64_t o, uint64_t n)
{
    uint64_t total = 0;

    if (o >= n) {
        return 0;
    }

    for (unsigned int k = 0; k < 64U; ++k) {
        uint64_t first;

        if (k == 63U) {
            first = UINT64_MAX;
        } else {
            const uint64_t mask =
                (UINT64_C(1) << (k + 1U)) - UINT64_C(1);
            first = o | mask;
        }

        if (first <= o || first > n) {
            continue;
        }

        if (k == 63U) {
            ++total;
        } else {
            total += UINT64_C(1) + ((n - first) >> (k + 1U));
        }
    }

    return total;
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
        parsed > (uintmax_t)UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    uint64_t o;
    uint64_t n;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <o> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &o) ||
        !parse_uint64(argv[2], &n) ||
        o > n) {
        fprintf(stderr, "Invalid range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum_consecutive_hamming_distances(o, n));
    return EXIT_SUCCESS;
}