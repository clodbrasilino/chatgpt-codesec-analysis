#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool ends_with_number(const char *str, size_t length)
{
    return str != NULL
        && length > 0
        && isdigit((unsigned char)str[length - 1]) != 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity || new_capacity > SIZE_MAX - 1) {
                free(input);
                fputs("Input is too large.\n", stderr);
                return 1;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    puts(ends_with_number(input, length) ? "true" : "false");

    free(input);
    return 0;
}