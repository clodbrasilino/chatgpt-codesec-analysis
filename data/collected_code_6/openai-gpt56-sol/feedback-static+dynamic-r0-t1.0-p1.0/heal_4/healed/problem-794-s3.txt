#include <stdbool.h>
#include <stdio.h>

enum { INPUT_SIZE = 1024 };

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

int main(void)
{
    char input[INPUT_SIZE + 2U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return 1;
        }
        input[0] = '\0';
    }

    size_t length = 0U;

    while (input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && length > INPUT_SIZE) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != '\r' && ch != EOF);

        if (ch == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
                fputs("ungetc failed\n", stderr);
                return 1;
            }
        }

        if (ferror(stdin)) {
            perror("getchar");
            return 1;
        }

        fputs("Input exceeds maximum length\n", stderr);
        return 1;
    }

    input[length] = '\0';

    puts(matches_pattern(input, length) ? "Match" : "No match");
    return 0;
}