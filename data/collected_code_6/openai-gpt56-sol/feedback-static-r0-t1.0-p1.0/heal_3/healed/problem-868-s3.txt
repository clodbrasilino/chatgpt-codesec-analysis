#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t length_of_last_word(const char *str)
{
    size_t last_length = 0;
    size_t current_length = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isspace((unsigned char)*str)) {
            if (current_length != 0) {
                last_length = current_length;
                current_length = 0;
            }
        } else {
            ++current_length;
        }

        ++str;
    }

    return current_length != 0 ? current_length : last_length;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch = EOF;

    for (;;) {
        ch = getchar();

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            const size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 128 : capacity;
            char *new_input;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (printf("%zu\n", length_of_last_word(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}