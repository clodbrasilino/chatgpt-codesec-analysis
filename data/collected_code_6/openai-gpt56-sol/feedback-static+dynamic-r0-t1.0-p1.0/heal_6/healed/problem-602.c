#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};
    size_t i;

    if (data == NULL || result == NULL) {
        return 0;
    }

    for (i = 0U; i < length; ++i) {
        unsigned char current = data[i];

        if (seen[current] != 0U) {
            *result = current;
            return 1;
        }

        seen[current] = 1U;
    }

    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int ch;
    unsigned char repeated;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_input;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0U) {
        if (puts("No repeated character") == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    } else if (find_first_repeated_character(input, length, &repeated)) {
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