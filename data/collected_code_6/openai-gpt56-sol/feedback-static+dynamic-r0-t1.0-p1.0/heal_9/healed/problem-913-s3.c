#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static bool ends_with_number(const char *string, size_t length)
{
    return string != NULL &&
           length > 0 &&
           isdigit((unsigned char)string[length - 1]) != 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;

    for (;;) {
        int ch = getchar();

        if (ch == EOF || ch == '\n' || ch == '\r') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        size_t required = length + 2;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
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

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (ends_with_number(input, length)) {
        puts("The string ends with a number.");
    } else {
        puts("The string does not end with a number.");
    }

    free(input);
    return EXIT_SUCCESS;
}