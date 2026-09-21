#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *string)
{
    return string != NULL &&
           string[0] == 'a' &&
           string[1] == 'b' &&
           string[2] == 'b' &&
           (string[3] == '\0' ||
            (string[3] == 'b' && string[4] == '\0'));
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return 1;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            return 1;
        }
    }

    input[length] = '\0';

    if (puts(matches_pattern(input) ? "Match" : "No match") == EOF) {
        free(input);
        return 1;
    }

    free(input);
    return 0;
}