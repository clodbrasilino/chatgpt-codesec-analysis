#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void remove_non_alphanumeric(char *str)
{
    if (str == NULL) {
        return;
    }

    const unsigned char *read_ptr = (const unsigned char *)str;
    char *write_ptr = str;

    while (*read_ptr != '\0') {
        if (isalnum(*read_ptr)) {
            *write_ptr++ = (char)*read_ptr;
        }
        ++read_ptr;
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch = EOF;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    new_capacity = SIZE_MAX;
                } else {
                    new_capacity = capacity * 2;
                }
            }

            if (new_capacity <= length + 1) {
                free(input);
                return EXIT_FAILURE;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';
    remove_non_alphanumeric(input);

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}