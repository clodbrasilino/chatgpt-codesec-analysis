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
    static const size_t maximum_length = 255U;
    char input[maximum_length + 2U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > maximum_length) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        puts("No match");
        return 0;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");
    return 0;
}