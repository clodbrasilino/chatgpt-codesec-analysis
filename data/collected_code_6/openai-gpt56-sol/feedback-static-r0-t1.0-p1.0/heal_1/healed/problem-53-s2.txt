#include <stdbool.h>
#include <stdio.h>

static bool first_and_last_are_equal(const char *string, size_t length)
{
    return string != NULL && length > 0U && string[0] == string[length - 1U];
}

int main(void)
{
    char input[1024];
    size_t length = 0U;
    int character;

    while (length < sizeof input && (character = getchar()) != EOF &&
           character != '\n' && character != '\r') {
        input[length++] = (char)character;
    }

    if (character == '\r') {
        int next = getchar();

        if (next != '\n' && next != EOF) {
            ungetc(next, stdin);
        }
    }

    if (character == EOF && length == 0U) {
        return 1;
    }

    if (length == sizeof input &&
        character != '\n' && character != '\r' && character != EOF) {
        while ((character = getchar()) != '\n' &&
               character != '\r' && character != EOF) {
        }
        fputs("Input too long\n", stderr);
        return 1;
    }

    puts(first_and_last_are_equal(input, length) ? "Equal" : "Not equal");
    return 0;
}