#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_occurring_character(const unsigned char *data, size_t length,
                                  unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;

    if (data == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned int index = data[i];

        if (frequencies[index] == SIZE_MAX) {
            return 0;
        }

        ++frequencies[index];
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            *result = (unsigned char)i;
        }
    }

    return 1;
}

int main(void)
{
    unsigned char *data = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char result;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_data;

            if (capacity == 0) {
                new_capacity = 256;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    fputs("Input is too long.\n", stderr);
                    free(data);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2;
            }

            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                free(data);
                return EXIT_FAILURE;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        free(data);
        return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(data, length, &result)) {
        fputs("Input must not be empty or is too long.\n", stderr);
        free(data);
        return EXIT_FAILURE;
    }

    free(data);

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}