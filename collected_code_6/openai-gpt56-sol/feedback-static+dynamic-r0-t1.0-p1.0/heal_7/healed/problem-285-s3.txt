#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           (length == 3U || length == 4U) &&
           string[0] == 'a' &&
           string[1] == 'b' &&
           string[2] == 'b' &&
           (length == 3U || string[3] == 'b');
}

static bool read_input(char *buffer, size_t capacity, size_t *length,
                       bool *too_long)
{
    int character;
    size_t used = 0U;

    if (buffer == NULL || length == NULL || too_long == NULL ||
        capacity == 0U) {
        return false;
    }

    *too_long = false;

    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
                return false;
            }
            break;
        }

        if (used + 1U < capacity) {
            buffer[used++] = (char)character;
        } else {
            *too_long = true;
        }
    }

    if (ferror(stdin)) {
        return false;
    }

    buffer[used] = '\0';
    *length = used;
    return true;
}

int main(void)
{
    char input[5];
    size_t length;
    bool too_long;

    if (!read_input(input, sizeof input, &length, &too_long)) {
        return 1;
    }

    if (!too_long && matches_pattern(input, length)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}