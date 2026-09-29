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

static bool discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

int main(void)
{
    static const char pattern[] = "abbb";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[sizeof pattern + 1U];

    if (fgets(input, (int)sizeof input, stdin) == NULL) {
        return 1;
    }

    const size_t length = strcspn(input, "\n");

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        if (!discard_line()) {
            return 1;
        }

        puts("No match");
        return 0;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");
    return 0;
}