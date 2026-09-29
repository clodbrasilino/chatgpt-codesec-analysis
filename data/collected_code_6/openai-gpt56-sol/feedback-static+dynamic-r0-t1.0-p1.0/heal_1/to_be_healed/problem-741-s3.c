#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool all_characters_same(const char *str)
{
    if (str == NULL || str[0] == '\0') {
        return false;
    }

    for (size_t i = 1; str[i] != '\0'; ++i) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
        fprintf(stderr, "No input provided.\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else if (length == sizeof input - 1 && !feof(stdin)) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Input is too long.\n");
        return 1;
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    if (all_characters_same(input)) {
        puts("All characters are the same.");
    } else {
        puts("Not all characters are the same.");
    }

    return 0;
}