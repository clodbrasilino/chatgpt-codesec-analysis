#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 128U;
    size_t used = 0U;
    char *input;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0U;

    input = malloc(capacity);
    if (input == NULL) {
        return -1;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(input);
                return -1;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            int next_character = fgetc(stdin);

            if (next_character == EOF) {
                if (ferror(stdin)) {
                    free(input);
                    return -1;
                }
            } else if (next_character != '\n' &&
                       ungetc(next_character, stdin) == EOF) {
                free(input);
                return -1;
            }
            break;
        }

        if (used == capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return -1;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return -1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[used++] = (char)(unsigned char)character;
    }

    input[used] = '\0';
    *buffer = input;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    int result = EXIT_SUCCESS;

    if (read_line(&input, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(matches_pattern(input, length) ? "Match" : "No match") == EOF) {
        result = EXIT_FAILURE;
    }

    free(input);
    return result;
}