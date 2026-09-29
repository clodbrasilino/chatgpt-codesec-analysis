#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_multiple_spaces(char *str)
{
    char *read_ptr;
    char *write_ptr;
    int previous_was_space = 0;

    if (str == NULL) {
        return;
    }

    read_ptr = str;
    write_ptr = str;

    while (*read_ptr != '\0') {
        if (*read_ptr != ' ' || !previous_was_space) {
            *write_ptr++ = *read_ptr;
        }

        previous_was_space = (*read_ptr == ' ');
        ++read_ptr;
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *input;
    size_t length = 0;
    size_t capacity = 128;
    int ch = EOF;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < required) {
                    new_capacity = required;
                }
            }

            new_input = realloc(input, new_capacity);
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

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    input[length] = '\0';
    remove_multiple_spaces(input);

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}