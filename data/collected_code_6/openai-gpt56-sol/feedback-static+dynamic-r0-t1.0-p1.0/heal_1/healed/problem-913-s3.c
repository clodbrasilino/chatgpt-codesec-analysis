#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool ends_with_number(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           isdigit((unsigned char)string[length - 1U]) != 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    while ((character = fgetc(stdin)) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin) != 0) {
        free(input);
        return 1;
    }

    if (ends_with_number(input, length)) {
        puts("The string ends with a number.");
    } else {
        puts("The string does not end with a number.");
    }

    free(input);
    return 0;
}