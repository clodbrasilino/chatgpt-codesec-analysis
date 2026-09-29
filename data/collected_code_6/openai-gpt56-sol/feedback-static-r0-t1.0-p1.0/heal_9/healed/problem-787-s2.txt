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
    bool too_long = false;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length < sizeof input - 1U) {
            input[length++] = (char)ch;
        } else {
            too_long = true;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        return 1;
    }

    if (ch == EOF && length == 0U && !too_long) {
        return 1;
    }

    input[length] = '\0';

    puts(!too_long && matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}