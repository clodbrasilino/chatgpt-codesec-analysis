#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string)
{
    size_t length;

    if (string == NULL) {
        return false;
    }

    length = strlen(string);

    return length >= 2U && string[0] == 'a' && string[length - 1U] == 'b';
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if (matches_pattern(input)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}