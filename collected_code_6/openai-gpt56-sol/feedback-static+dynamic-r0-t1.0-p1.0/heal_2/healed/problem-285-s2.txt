#include <stdbool.h>
#include <stdio.h>

static bool matches_pattern(const char *string)
{
    if (string == NULL) {
        return false;
    }

    return string[0] == 'a' &&
           string[1] == 'b' &&
           string[2] == 'b' &&
           (string[3] == '\0' ||
            (string[3] == 'b' && string[4] == '\0'));
}

int main(void)
{
    char input[6];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0;

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int character;
        bool read_error = false;

        while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        }

        if (character == EOF && ferror(stdin)) {
            read_error = true;
        }

        if (read_error) {
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