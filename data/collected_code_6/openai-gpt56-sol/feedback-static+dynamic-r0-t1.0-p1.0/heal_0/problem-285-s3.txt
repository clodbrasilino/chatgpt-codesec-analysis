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

    return (length == 3U || length == 4U) &&
           string[0] == 'a' &&
           string[1] == 'b' &&
           string[2] == 'b' &&
           (length == 3U || string[3] == 'b');
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        return 0;
    }

    input[strcspn(input, "\r\n")] = '\0';

    puts(matches_pattern(input) ? "Match" : "No match");

    return 0;
}