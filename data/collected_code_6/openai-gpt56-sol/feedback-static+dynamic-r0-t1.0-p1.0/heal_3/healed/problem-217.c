#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1] = {0};

    if (data == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = data[i];

        if (seen[ch] != 0) {
            *result = ch;
            return 1;
        }

        seen[ch] = 1;
    }

    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char repeated;
    int c;

    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (length == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            unsigned char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)c;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (find_first_repeated_character(input, length, &repeated)) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}