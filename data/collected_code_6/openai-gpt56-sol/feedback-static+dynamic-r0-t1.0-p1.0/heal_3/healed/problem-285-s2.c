#include <stdbool.h>
#include <stdio.h>

static bool matches_pattern(const char *string)
{
    if (string == NULL) {
        return false;
    }

    return (string[0] == 'a' &&
            string[1] == 'b' &&
            string[2] == 'b' &&
            string[3] == '\0') ||
           (string[0] == 'a' &&
            string[1] == 'b' &&
            string[2] == 'b' &&
            string[3] == 'b' &&
            string[4] == '\0');
}

int main(void)
{
    char input[6];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (length == sizeof input || !feof(stdin)) {
        int character;

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        if (ferror(stdin)) {
            return 1;
        }

        if (puts("No match") == EOF) {
            return 1;
        }

        return 0;
    }

    if (puts(matches_pattern(input) ? "Match" : "No match") == EOF) {
        return 1;
    }

    return 0;
}