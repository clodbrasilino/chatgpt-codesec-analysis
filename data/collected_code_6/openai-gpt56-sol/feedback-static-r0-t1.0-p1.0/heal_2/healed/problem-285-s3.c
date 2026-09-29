#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           (length == 3U || length == 4U) &&
           string[0] == 'a' &&
           string[1] == 'b' &&
           string[2] == 'b' &&
           (length == 3U || string[3] == 'b');
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != '\n' &&
           character != '\r' &&
           character != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 16U : capacity * 2U;
            char *resized;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == '\r') {
        int next_character = fgetc(stdin);

        if (next_character != '\n' && next_character != EOF) {
            ungetc(next_character, stdin);
        }
    }

    if (ferror(stdin) != 0) {
        free(input);
        return 1;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");

    free(input);
    return 0;
}