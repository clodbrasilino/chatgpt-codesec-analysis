#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 256U

static bool can_rearrange_without_equal_adjacent(const char *str, size_t length)
{
    size_t frequencies[UCHAR_MAX + 1U] = {0};
    size_t max_frequency = 0;

    if (str == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)str[i];

        ++frequencies[character];

        if (frequencies[character] > max_frequency) {
            max_frequency = frequencies[character];
        }
    }

    return max_frequency <= (length / 2U) + (length % 2U);
}

int main(void)
{
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;
    char *input = malloc(capacity);
    int character;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *resized_input;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            resized_input = realloc(input, new_capacity);

            if (resized_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    if (puts(can_rearrange_without_equal_adjacent(input, length)
                 ? "true"
                 : "false") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}