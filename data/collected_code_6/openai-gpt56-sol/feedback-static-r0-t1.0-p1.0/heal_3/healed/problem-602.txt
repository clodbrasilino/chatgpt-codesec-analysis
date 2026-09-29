#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const char *str, unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (str == NULL || result == NULL) {
        return 0;
    }

    for (const unsigned char *current = (const unsigned char *)str;
         *current != '\0';
         ++current) {
        if (seen[*current] != 0U) {
            *result = *current;
            return 1;
        }

        seen[*current] = 1U;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    unsigned char repeated = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1U) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length + 1U) {
                free(input);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    if (capacity <= length) {
        char *new_input = realloc(input, length + 1U);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        capacity = length + 1U;
    }

    input[length] = '\0';

    if (find_first_repeated_character(input, &repeated) != 0) {
        printf("%c\n", (int)repeated);
    } else {
        puts("No repeated character");
    }

    free(input);
    return EXIT_SUCCESS;
}