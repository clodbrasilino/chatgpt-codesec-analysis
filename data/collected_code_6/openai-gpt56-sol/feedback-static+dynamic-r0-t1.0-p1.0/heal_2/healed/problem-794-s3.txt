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
    char input[INPUT_SIZE];
    size_t length = 0U;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
        if (length < sizeof input) {
            input[length++] = (char)ch;
        }
    }

    if (ferror(stdin)) {
        perror("getchar");
        return 1;
    }

    if (ch == '\r') {
        int next = getchar();

        if (next != '\n' && next != EOF) {
            if (ungetc(next, stdin) == EOF) {
                fputs("ungetc failed\n", stderr);
                return 1;
            }
        }

        if (ferror(stdin)) {
            perror("getchar");
            return 1;
        }
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}