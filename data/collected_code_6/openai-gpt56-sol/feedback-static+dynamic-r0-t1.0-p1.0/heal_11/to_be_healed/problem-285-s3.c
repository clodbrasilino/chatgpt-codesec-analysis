#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           string[0] == 'a' &&
           string[1] == 'b' &&
           string[2] == 'b' &&
           (length == 3U || (length == 4U && string[3] == 'b'));
}

static bool read_input(char *buffer, size_t capacity, size_t *length,
                       bool *too_long)
{
    size_t used = 0U;
    int character;

    if (buffer == NULL || capacity == 0U ||
        length == NULL || too_long == NULL) {
        return false;
    }

    buffer[0] = '\0';
    *length = 0U;
    *too_long = false;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' &&
           character != '\r' &&
           character != EOF) {
        if (used + 1U < capacity) {
            buffer[used++] = (char)character;
        } else {
            *too_long = true;
        }
    }

    if (character == '\r') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();
        if (character != '\n' && character != EOF &&
            ungetc(character, stdin) == EOF) {
            return false;
        }
    }

    if (ferror(stdin)) {
        return false;
    }

    if (character == EOF && used == 0U && !*too_long) {
        return false;
    }

    buffer[used] = '\0';
    *length = used;

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[5];
    size_t length;
    bool too_long;

    if (!read_input(input, sizeof input, &length, &too_long)) {
        return 1;
    }

    puts(!too_long && matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}