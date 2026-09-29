#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static bool discard_line(void)
{
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return true;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    char input[INPUT_CAPACITY + 2U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("stdin");
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    size_t length = strcspn(input, "\r\n");

    if (input[length] == '\r' || input[length] == '\n') {
        input[length] = '\0';
    } else if (length > INPUT_CAPACITY) {
        if (!discard_line()) {
            perror("stdin");
            return EXIT_FAILURE;
        }

        fputs("Input too long\n", stderr);
        return EXIT_FAILURE;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");
    return EXIT_SUCCESS;
}