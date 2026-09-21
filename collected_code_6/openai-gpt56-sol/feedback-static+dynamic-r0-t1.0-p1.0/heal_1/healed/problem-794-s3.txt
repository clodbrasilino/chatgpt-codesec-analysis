#include <stdbool.h>
#include <stdio.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

int main(void)
{
    char input[1024];
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
            ungetc(next, stdin);
        }

        if (ferror(stdin)) {
            perror("getchar");
            return 1;
        }
    }

    if (matches_pattern(input, length)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}