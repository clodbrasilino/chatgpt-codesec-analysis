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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char discard[256];
        bool newline_found = false;

        while (fgets(discard, sizeof discard, stdin) != NULL) {
            if (strchr(discard, '\n') != NULL) {
                newline_found = true;
                break;
            }
        }

        if (!newline_found) {
            return 1;
        }

        puts("No match");
        return 0;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");
    return 0;
}