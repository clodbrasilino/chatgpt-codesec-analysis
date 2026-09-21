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
    char input[6];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    char *newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else if (!feof(stdin)) {
        int character;

        while ((character = getchar()) != '\n' && character != EOF) {
        }

        if (ferror(stdin)) {
            return 1;
        }

        return puts("No match") == EOF ? 1 : 0;
    }

    return puts(matches_pattern(input) ? "Match" : "No match") == EOF ? 1 : 0;
}