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
    size_t capacity = 256;
    size_t length = 0;
    unsigned char *data = malloc(capacity);
    unsigned char result;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (data == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        if (fgets(input, sizeof input, stdin) == NULL) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(data);
                return EXIT_FAILURE;
            }
            break;
        }

        size_t chunk_length = 0;

        while (chunk_length < sizeof input && input[chunk_length] != '\0' &&
               input[chunk_length] != '\n') {
            ++chunk_length;
        }

        if (chunk_length > SIZE_MAX - length) {
            fputs("Input is too long.\n", stderr);
            free(data);
            return EXIT_FAILURE;
        }

        size_t required = length + chunk_length;

        if (required > capacity) {
            size_t new_capacity = capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            unsigned char *new_data = realloc(data, new_capacity);

            if (new_data == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                free(data);
                return EXIT_FAILURE;
            }

            data = new_data;
            capacity = new_capacity;
        }

        for (size_t i = 0; i < chunk_length; ++i) {
            data[length + i] = (unsigned char)input[i];
        }
        length = required;

        if (chunk_length < sizeof input && input[chunk_length] == '\n') {
            break;
        }
    }

    if (!find_max_occurring_character(data, length, &result)) {
        fputs(length == 0 ? "Input must not be empty.\n"
                          : "Failed to process input.\n",
              stderr);
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