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
    char input[INPUT_CAPACITY + 1U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("stdin");
            return 1;
        }
        return 0;
    }

    size_t length = 0U;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n' && input[length] != '\r') {
        ++length;
    }

    if (length < sizeof input &&
        (input[length] == '\n' || input[length] == '\r')) {
        input[length] = '\0';
    } else if (length == INPUT_CAPACITY) {
        int ch = getchar();

        if (ch != '\n' && ch != '\r' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != '\r' && ch != EOF) {
            }

            if (ferror(stdin)) {
                perror("stdin");
                return 1;
            }

            fputs("Input too long\n", stderr);
            return 1;
        }
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");
    return 0;
}