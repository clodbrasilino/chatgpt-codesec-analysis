#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *str, size_t length)
{
    static const char pattern[] = "abbb";

    return str != NULL &&
           length == sizeof pattern - 1U &&
           memcmp(str, pattern, sizeof pattern - 1U) == 0;
}

int main(void)
{
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length == sizeof input - 1U) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch != '\n') {
            return 1;
        }
    }

    if (matches_pattern(input, length)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}