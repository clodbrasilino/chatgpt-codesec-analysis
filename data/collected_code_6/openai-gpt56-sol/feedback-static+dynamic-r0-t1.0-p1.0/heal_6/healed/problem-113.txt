#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

bool is_integer(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    const unsigned char *p = (const unsigned char *)str;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    if (*p == '\0') {
        return false;
    }

    while (*p != '\0') {
        if (!isdigit(*p)) {
            return false;
        }
        ++p;
    }

    return true;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch = EOF;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
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

            char *temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
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

    if (puts(is_integer(input) ? "true" : "false") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}