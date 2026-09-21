#include <stdbool.h>
#include <stdio.h>

static bool first_and_last_are_equal(const char *string, size_t length)
{
    return string != NULL && length > 0U &&
           string[0] == string[length - 1U];
}

int main(void)
{
    char input[1024];
    size_t length = 0U;
    int character = EOF;

    while (length < sizeof input) {
        character = getchar();

        if (character == EOF || character == '\n' || character == '\r') {
            break;
        }

        input[length++] = (char)character;
    }

    if (character == '\r') {
        int next = getchar();

        if (next != '\n' && next != EOF) {
            if (ungetc(next, stdin) == EOF) {
                return 1;
            }
        }
    }

    if (character == EOF && length == 0U) {
        return 1;
    }

    if (length == sizeof input) {
        character = getchar();

        if (character != '\n' && character != '\r' && character != EOF) {
            do {
                character = getchar();
            } while (character != '\n' &&
                     character != '\r' &&
                     character != EOF);

            if (character == '\r') {
                int next = getchar();

                if (next != '\n' && next != EOF) {
                    (void)ungetc(next, stdin);
                }
            }

            fputs("Input too long\n", stderr);
            return 1;
        }

        if (character == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    return 1;
                }
            }
        }
    }

    puts(first_and_last_are_equal(input, length) ? "Equal" : "Not equal");
    return 0;
}