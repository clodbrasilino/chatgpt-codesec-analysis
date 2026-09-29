#include <stdbool.h>
#include <stdio.h>

enum {
    INPUT_CAPACITY = 1024
};

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

int main(void)
{
    char input[INPUT_CAPACITY];
    size_t length = 0U;
    int ch = EOF;
    bool too_long = false;

    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    fputs("Input error\n", stderr);
                    return 1;
                }
            }

            break;
        }

        if (length < sizeof input) {
            input[length++] = (char)ch;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin)) {
        perror("stdin");
        return 1;
    }

    if (too_long) {
        fputs("Input too long\n", stderr);
        return 1;
    }

    if (length == 0U && ch == EOF) {
        return 0;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}