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

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n' && input[length] != '\r') {
        ++length;
    }

    if (length < sizeof input &&
        (input[length] == '\n' || input[length] == '\r')) {
        input[length] = '\0';
    } else if (length == sizeof input - 1U) {
        int character = getchar();

        if (character == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF &&
                ungetc(next, stdin) == EOF) {
                return 1;
            }
        } else if (character != '\n' && character != EOF) {
            too_long = true;

            while ((character = getchar()) != EOF &&
                   character != '\n' && character != '\r') {
            }

            if (character == '\r') {
                int next = getchar();

                if (next != '\n' && next != EOF &&
                    ungetc(next, stdin) == EOF) {
                    return 1;
                }
            }
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (!too_long && matches_pattern(input, length)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}