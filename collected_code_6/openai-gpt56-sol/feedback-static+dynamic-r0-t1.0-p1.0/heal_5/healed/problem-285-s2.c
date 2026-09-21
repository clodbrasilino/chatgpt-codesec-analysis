#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string)
{
    return string != NULL &&
           (strcmp(string, "abb") == 0 || strcmp(string, "abbb") == 0);
}

int main(void)
{
    char input[5];
    size_t length = 0;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length < sizeof input - 1) {
            input[length++] = (char)character;
        } else {
            while ((character = getchar()) != '\n' && character != EOF) {
            }

            if (ferror(stdin)) {
                return 1;
            }

            return puts("No match") == EOF ? 1 : 0;
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (character == EOF && length == 0) {
        return 0;
    }

    input[length] = '\0';

    return puts(matches_pattern(input) ? "Match" : "No match") == EOF ? 1 : 0;
}