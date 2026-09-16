#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *str)
{
    return str != NULL &&
           strlen(str) == 4U &&
           str[0] == 'a' &&
           str[1] == 'b' &&
           str[2] == 'b' &&
           str[3] == 'b';
}

int main(void)
{
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (matches_pattern(input)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}