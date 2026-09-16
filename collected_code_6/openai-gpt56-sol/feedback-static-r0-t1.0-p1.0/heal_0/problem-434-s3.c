#include <stdio.h>
#include <stdbool.h>

static bool matches(const char *str)
{
    if (str == NULL || *str != 'a') {
        return false;
    }

    ++str;

    if (*str != 'b') {
        return false;
    }

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    size_t length = 0;
    while (input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && !feof(stdin)) {
        int ch;
        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            return 1;
        }

        fprintf(stderr, "Input is too long.\n");
        return 1;
    }

    input[length] = '\0';

    puts(matches(input) ? "Match" : "No match");
    return 0;
}