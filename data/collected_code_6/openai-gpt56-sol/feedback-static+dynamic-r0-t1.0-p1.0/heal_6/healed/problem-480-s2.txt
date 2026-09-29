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
        if (frequencies[data[i]] == SIZE_MAX) {
            return 0;
        }
        ++frequencies[data[i]];
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
    size_t capacity = 4096;
    size_t length = 0;
    unsigned char *buffer = malloc(capacity);
    unsigned char result;
    int ch;

    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (unsigned char)ch;
    }

    if (ferror(stdin) ||
        !find_max_occurring_character(buffer, length, &result)) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}