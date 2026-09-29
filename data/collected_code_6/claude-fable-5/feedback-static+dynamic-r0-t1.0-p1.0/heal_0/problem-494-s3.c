#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int binary_tuple_to_int(const int *bits, size_t length, unsigned long *result)
{
    size_t i;
    unsigned long value = 0;

    if (bits == NULL || result == NULL) {
        return -1;
    }

    if (length == 0 || length > (sizeof(unsigned long) * CHAR_BIT)) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        if (bits[i] != 0 && bits[i] != 1) {
            return -1;
        }
        value = (value << 1) | (unsigned long)bits[i];
    }

    *result = value;
    return 0;
}

int main(void)
{
    int binary_tuple[] = {1, 0, 1, 1, 0, 1};
    size_t length = sizeof(binary_tuple) / sizeof(binary_tuple[0]);
    unsigned long result = 0;

    if (binary_tuple_to_int(binary_tuple, length, &result) != 0) {
        fprintf(stderr, "Error: invalid binary tuple input\n");
        return EXIT_FAILURE;
    }

    if (printf("The integer value is: %lu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}