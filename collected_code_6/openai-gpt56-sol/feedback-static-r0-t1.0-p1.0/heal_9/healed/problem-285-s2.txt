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
    size_t length;
    bool too_long = false;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int character;

        too_long = true;
        while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (puts(!too_long && matches_pattern(input, length)
                 ? "Match"
                 : "No match") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}