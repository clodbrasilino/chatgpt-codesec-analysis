#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int binary_tuple_to_int(const int *bits, size_t length, unsigned long *result)
{
    size_t i;
    unsigned long value = 0UL;

    if (bits == NULL || result == NULL || length == 0U) {
        return -1;
    }

    if (length > (sizeof(unsigned long) * CHAR_BIT)) {
        return -1;
    }

    for (i = 0U; i < length; i++) {
        if (bits[i] != 0 && bits[i] != 1) {
            return -1;
        }
        value = (value << 1U) | (unsigned long)bits[i];
    }

    *result = value;
    return 0;
}

int main(void)
{
    int binary_tuple[] = {1, 0, 1, 1, 0, 1};
    size_t length = sizeof(binary_tuple) / sizeof(binary_tuple[0]);
    unsigned long result = 0UL;

    if (binary_tuple_to_int(binary_tuple, length, &result) != 0) {
        if (fprintf(stderr, "Error: invalid binary tuple input.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("The converted integer is: %lu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}