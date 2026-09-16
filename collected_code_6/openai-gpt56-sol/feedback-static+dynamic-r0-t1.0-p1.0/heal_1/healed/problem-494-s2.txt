#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_tuple_to_uint64(const char *tuple, uint64_t *result)
{
    uint64_t value = 0;
    const unsigned char *cursor;

    if (tuple == NULL || result == NULL) {
        return 0;
    }

    cursor = (const unsigned char *)tuple;

    if (*cursor == '\0') {
        return 0;
    }

    while (*cursor != '\0') {
        uint64_t bit;

        if (*cursor == '0') {
            bit = UINT64_C(0);
        } else if (*cursor == '1') {
            bit = UINT64_C(1);
        } else {
            return 0;
        }

        if (value > (UINT64_MAX - bit) / UINT64_C(2)) {
            return 0;
        }

        value = value * UINT64_C(2) + bit;
        ++cursor;
    }

    *result = value;
    return 1;
}

int main(int argc, char *const argv[])
{
    uint64_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary-tuple>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!binary_tuple_to_uint64(argv[1], &value)) {
        fputs("Invalid binary tuple or integer overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}