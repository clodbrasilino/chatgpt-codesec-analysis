#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>

static int binary_tuple_to_uint64(const unsigned int *tuple, size_t length,
                                  uint64_t *result)
{
    uint64_t value = 0;

    if (tuple == NULL || result == NULL || length > 64U) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (tuple[i] > 1U) {
            return -1;
        }
        value = (value << 1U) | (uint64_t)tuple[i];
    }

    *result = value;
    return 0;
}

int main(void)
{
    const unsigned int tuple[] = {1U, 0U, 1U, 1U, 0U, 1U};
    const size_t length = sizeof(tuple) / sizeof(tuple[0]);
    uint64_t value = 0;

    if (binary_tuple_to_uint64(tuple, length, &value) != 0) {
        fputs("Invalid binary tuple\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", value) < 0) {
        return 1;
    }

    return 0;
}