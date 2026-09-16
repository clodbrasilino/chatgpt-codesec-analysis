#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>

int tuple_to_integer(const int *tuple, size_t length, long *result)
{
    size_t i;
    long value = 0;

    if (tuple == NULL || result == NULL || length == 0) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        int element = tuple[i];
        int divisor = 1;
        int temp;

        if (element <= 0) {
            return -1;
        }

        temp = element;
        while (temp >= 10) {
            if (divisor > INT_MAX / 10) {
                return -1;
            }
            divisor *= 10;
            temp /= 10;
        }

        while (divisor > 0) {
            int digit = (element / divisor) % 10;
            if (value > (LONG_MAX - digit) / 10) {
                return -1;
            }
            value = value * 10 + digit;
            divisor /= 10;
        }
    }

    *result = value;
    return 0;
}

int main(void)
{
    int tuple[] = {1, 23, 456};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    long result = 0;

    if (tuple_to_integer(tuple, length, &result) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Converted integer: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}