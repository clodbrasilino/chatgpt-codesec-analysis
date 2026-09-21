#include <stdbool.h>
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
    char input[5];
    size_t length = 0U;
    int character;

    while ((character = getchar()) != '\n' &&
           character != '\r' &&
           character != EOF) {
        if (length < sizeof(input)) {
            input[length] = (char)character;
        }
        ++length;
    }

    if (character == '\r') {
        int next = getchar();

        if (next != '\n' && next != EOF) {
            ungetc(next, stdin);
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (length > sizeof(input)) {
        puts("No match");
        return 0;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}