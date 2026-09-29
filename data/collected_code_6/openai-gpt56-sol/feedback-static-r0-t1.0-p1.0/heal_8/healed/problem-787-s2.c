#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *str, size_t length)
{
    static const char pattern[] = "abbb";
    const size_t pattern_length = sizeof pattern - 1U;

    return str != NULL &&
           length == pattern_length &&
           memcmp(str, pattern, pattern_length) == 0;
}

int main(void)
{
    static const char pattern[] = "abbb";
    char input[sizeof pattern];
    size_t length = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length < sizeof input) {
            input[length++] = (char)ch;
        } else {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ch == EOF && ferror(stdin)) {
                return 1;
            }

            puts("No match");
            return 0;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        return 1;
    }

    if (ch == EOF && length == 0U) {
        return 1;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");
    return 0;
}