#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           (length == 3U || length == 4U) &&
           string[0] == 'a' &&
           string[1] == 'b' &&
           string[2] == 'b' &&
           (length == 3U || string[3] == 'b');
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH + 1U];
    size_t length = 0U;
    int character = EOF;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (length >= MAX_INPUT_LENGTH) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((character = fgetc(stdin)) != EOF &&
                   character != '\n' &&
                   character != '\r') {
            }

            if (character == '\r') {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                int next_character = fgetc(stdin);

                if (next_character != '\n' && next_character != EOF) {
                    if (ungetc(next_character, stdin) == EOF) {
                        return EXIT_FAILURE;
                    }
                }
            }

            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }

            puts("No match");
            return EXIT_SUCCESS;
        }

        input[length++] = (char)character;
    }

    if (character == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next_character = fgetc(stdin);

        if (next_character != '\n' && next_character != EOF) {
            if (ungetc(next_character, stdin) == EOF) {
                return EXIT_FAILURE;
            }
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    puts(matches_pattern(input, length) ? "Match" : "No match");

    return EXIT_SUCCESS;
}