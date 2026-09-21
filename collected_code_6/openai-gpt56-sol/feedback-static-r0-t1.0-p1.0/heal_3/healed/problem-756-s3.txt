#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum { INPUT_SIZE = 1024 };

static bool matches(const char *string)
{
    return string != NULL &&
           (strcmp(string, "a") == 0 || strcmp(string, "ab") == 0);
}

int main(void)
{
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return 1;
        }
        return 0;
    }

    char *newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else if (!feof(stdin)) {
        int c;

        while ((c = getchar()) != '\n' && c != EOF) {
        }

        fputs("Input is too long\n", stderr);
        return 1;
    }

    puts(matches(input) ? "Match" : "No match");
    return 0;
}