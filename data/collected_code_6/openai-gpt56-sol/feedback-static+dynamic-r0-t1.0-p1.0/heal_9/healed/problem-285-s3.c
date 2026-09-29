#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           ((length == 3U && memcmp(string, "abb", 3U) == 0) ||
            (length == 4U && memcmp(string, "abbb", 4U) == 0));
}

static bool read_input(char *buffer, size_t capacity, size_t *length,
                       bool *too_long)
{
    char line[256];
    size_t used;
    int character;

    if (buffer == NULL || capacity == 0U ||
        length == NULL || too_long == NULL) {
        return false;
    }

    buffer[0] = '\0';
    *length = 0U;
    *too_long = false;

    if (fgets(line, sizeof line, stdin) == NULL) {
        return false;
    }

    used = strcspn(line, "\r\n");

    if (line[used] == '\0' && used == sizeof line - 1U) {
        while ((character = fgetc(stdin)) != '\n' &&
               character != '\r' &&
               character != EOF) {
        }

        if (character == '\r') {
            character = fgetc(stdin);
            if (character != '\n' && character != EOF &&
                ungetc(character, stdin) == EOF) {
                return false;
            }
        }

        if (ferror(stdin)) {
            return false;
        }

        *too_long = true;
    } else if (line[used] == '\r' && line[used + 1U] == '\0') {
        character = fgetc(stdin);
        if (character != '\n' && character != EOF &&
            ungetc(character, stdin) == EOF) {
            return false;
        }
    }

    if (used >= capacity) {
        *too_long = true;
        used = capacity - 1U;
    }

    memcpy(buffer, line, used);
    buffer[used] = '\0';
    *length = used;

    return !ferror(stdin);
}

int main(void)
{
    char input[5];
    size_t length;
    bool too_long;

    if (!read_input(input, sizeof input, &length, &too_long)) {
        return 1;
    }

    puts(!too_long && matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}