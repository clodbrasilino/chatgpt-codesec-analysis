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

    while (length < sizeof input && (ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            ch = fgetc(stdin);
            if (ch != '\n' && ch != EOF) {
                ungetc(ch, stdin);
            }
            break;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        perror("fgetc");
        return 1;
    }

    if (length == sizeof input) {
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            if (ferror(stdin)) {
                perror("fgetc");
                return 1;
            }

            fputs("Input too long\n", stderr);
            return 1;
        }
    }

    if (length == 0U && ch == EOF) {
        return 0;
    }

    if (matches_pattern(input, length)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}