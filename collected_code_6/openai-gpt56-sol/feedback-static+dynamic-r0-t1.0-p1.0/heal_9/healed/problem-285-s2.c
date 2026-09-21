#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 5

static bool matches_pattern(const char *string)
{
    return string != NULL &&
           (strcmp(string, "abb") == 0 || strcmp(string, "abbb") == 0);
}

static bool discard_line(void)
{
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    }

    return !ferror(stdin);
}

int main(void)
{
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            if (!discard_line()) {
                return 1;
            }

            return puts("No match") == EOF ? 1 : 0;
        }

        if (character == EOF && ferror(stdin)) {
            return 1;
        }
    }

    return puts(matches_pattern(input) ? "Match" : "No match") == EOF ? 1 : 0;
}