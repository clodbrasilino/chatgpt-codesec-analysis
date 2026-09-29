#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           (length == 3U || length == 4U) &&
           string[0] == 'a' &&
           string[1] == 'b' &&
           string[2] == 'b' &&
           (length == 3U || string[3] == 'b');
}

static bool read_input(char *buffer, size_t capacity, size_t *length,
                       bool *too_long)
{
    int character;
    size_t used = 0U;

    if (buffer == NULL || length == NULL || too_long == NULL ||
        capacity == 0U) {
        return false;
    }

    *length = 0U;
    *too_long = false;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
                return false;
            }
            break;
        }

        if (used < capacity - 1U) {
            buffer[used++] = (char)character;
        } else {
            *too_long = true;
        }
    }

    if (ferror(stdin)) {
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
    size_t length = 0U;
    bool too_long = false;

    if (!read_input(input, sizeof input, &length, &too_long)) {
        return 1;
    }

    puts(!too_long && matches_pattern(input, length) ? "Match" : "No match");

    return 0;
}