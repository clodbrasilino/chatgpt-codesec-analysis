#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

int main(void)
{
    char input[1024];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    length = strcspn(input, "\r\n");

    if (input[length] == '\r' || input[length] == '\n') {
        input[length] = '\0';
    } else if (length == sizeof input - 1U) {
        int character = getchar();

        if (character != '\n' && character != EOF) {
            while ((character = getchar()) != '\n' && character != EOF) {
            }
            puts("No match");
            return 0;
        }
    }

    if (matches_pattern(input, length)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}