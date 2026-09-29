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
    const size_t pattern_length = sizeof pattern - 1U;
    char input[sizeof pattern];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length == pattern_length) {
        const int next = fgetc(stdin);

        if (next != '\n' && next != EOF) {
            int ch;

            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ferror(stdin)) {
                return 1;
            }

            puts("No match");
            return 0;
        }

        if (next == EOF && ferror(stdin)) {
            return 1;
        }
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");
    return 0;
}