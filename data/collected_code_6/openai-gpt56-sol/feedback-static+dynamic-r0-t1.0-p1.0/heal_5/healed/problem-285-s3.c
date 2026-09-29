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

int main(void)
{
    char input[5] = {0};
    size_t length = 0U;
    bool too_long = false;
    int character = EOF;

    while ((character = getchar()) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (length < sizeof input - 1U) {
            input[length++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (character == '\r') {
        int next = getchar();

        if (next != '\n' && next != EOF) {
            if (ungetc(next, stdin) == EOF) {
                return 1;
            }
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    input[length] = '\0';

    if (!too_long && matches_pattern(input, length)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}