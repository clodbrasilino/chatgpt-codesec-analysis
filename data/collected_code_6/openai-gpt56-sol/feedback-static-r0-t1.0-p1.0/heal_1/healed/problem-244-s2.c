#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int next_perfect_square(uint64_t number, uint64_t *result)
{
    uint64_t low = 0;
    uint64_t high = UINT32_MAX;
    uint64_t root = 0;

    if (result == NULL) {
        return 0;
    }

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;

        if (mid == 0 || mid <= number / mid) {
            root = mid;

            if (mid == UINT32_MAX) {
                break;
            }

            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (root == UINT32_MAX) {
        return 0;
    }

    ++root;

    if (root > UINT64_MAX / root) {
        return 0;
    }

    *result = root * root;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!next_perfect_square((uint64_t)parsed, &result)) {
        fprintf(stderr, "No greater perfect square fits in uint64_t\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}