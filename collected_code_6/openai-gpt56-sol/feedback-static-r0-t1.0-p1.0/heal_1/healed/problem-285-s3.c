#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           (length == 3U || length == 4U) &&
           string[0] == 'a' &&
           string[1] == 'b' &&
           string[2] == 'b' &&
           (length == 3U || string[3] == 'b');
}

int main(void)
{
    char input[1024];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) != 0 ? 1 : 0;
    }

    length = strcspn(input, "\r\n");

    if (input[length] != '\0') {
        input[length] = '\0';
    } else if (length == sizeof input - 1U) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        puts("No match");
        return ferror(stdin) != 0 ? 1 : 0;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}