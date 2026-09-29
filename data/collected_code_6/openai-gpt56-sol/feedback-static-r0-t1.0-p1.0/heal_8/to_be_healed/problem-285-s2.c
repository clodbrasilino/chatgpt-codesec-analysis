#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *string, size_t length)
{
    if (string == NULL) {
        return false;
    }

    return (length == 3U &&
            string[0] == 'a' &&
            string[1] == 'b' &&
            string[2] == 'b') ||
           (length == 4U &&
            string[0] == 'a' &&
            string[1] == 'b' &&
            string[2] == 'b' &&
            string[3] == 'b');
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[5];
    size_t length = 0U;
    bool too_long = false;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length < sizeof(input) - 1U) {
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