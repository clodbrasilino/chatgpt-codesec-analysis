#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int binary_tuple_to_int(const int *tuple, size_t length, unsigned long *result)
{
    if (tuple == NULL || result == NULL || length == 0U) {
        return -1;
    }

    if (length > (size_t)(sizeof(unsigned long) * CHAR_BIT)) {
        return -1;
    }

    unsigned long value = 0UL;

    for (size_t i = 0U; i < length; i++) {
        if (tuple[i] != 0 && tuple[i] != 1) {
            return -1;
        }
        value = (value << 1U) | (unsigned long)tuple[i];
    }

    *result = value;
    return 0;
}

int main(void)
{
    int tuple[] = {1, 0, 1, 1, 0, 1};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    unsigned long result = 0UL;

    if (binary_tuple_to_int(tuple, length, &result) != 0) {
        fprintf(stderr, "Error: invalid binary tuple input\n");
        return EXIT_FAILURE;
    }

    if (printf("Binary tuple converts to: %lu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}