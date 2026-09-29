#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool matches_pattern(const char *string, size_t length)
{
    static const char pattern1[] = "abb";
    static const char pattern2[] = "abbb";

    return string != NULL &&
           ((length == sizeof(pattern1) - 1U &&
             memcmp(string, pattern1, sizeof(pattern1) - 1U) == 0) ||
            (length == sizeof(pattern2) - 1U &&
             memcmp(string, pattern2, sizeof(pattern2) - 1U) == 0));
}

int main(void)
{
    char input[5];
    size_t length = 0U;
    bool too_long = false;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1U < sizeof(input)) {
            input[length++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (puts(!too_long && matches_pattern(input, length)
                 ? "Match"
                 : "No match") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}