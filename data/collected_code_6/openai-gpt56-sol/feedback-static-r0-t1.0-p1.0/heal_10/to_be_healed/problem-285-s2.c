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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
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