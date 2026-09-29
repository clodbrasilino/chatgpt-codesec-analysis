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
    char input[sizeof pattern + 1U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(input, "\n");
    bool too_long = input[length] != '\n' && !feof(stdin);

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (too_long) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            return 1;
        }
    }

    puts(!too_long && matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}