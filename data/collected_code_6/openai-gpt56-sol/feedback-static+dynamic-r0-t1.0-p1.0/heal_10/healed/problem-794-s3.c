#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum { INPUT_SIZE = 1024 };

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

static int read_line(char *buffer, size_t capacity, size_t *length)
{
    size_t used = 0U;
    int ch;

    if (buffer == NULL || length == NULL || capacity == 0U) {
        return -1;
    }

    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    return -1;
                }
            }

            break;
        }

        if (used + 1U >= capacity) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            if (ferror(stdin)) {
                return -1;
            }

            return 1;
        }

        buffer[used++] = (char)ch;
    }

    if (ferror(stdin)) {
        return -1;
    }

    if (ch == EOF && used == 0U) {
        return 2;
    }

    buffer[used] = '\0';
    *length = used;
    return 0;
}

int main(void)
{
    char input[INPUT_SIZE + 1U];
    size_t length = 0U;
    int result = read_line(input, sizeof input, &length);

    if (result < 0) {
        perror("input");
        return 1;
    }

    if (result == 1) {
        fputs("Input exceeds maximum length\n", stderr);
        return 1;
    }

    if (result == 2) {
        puts("No match");
        return 0;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");
    return 0;
}