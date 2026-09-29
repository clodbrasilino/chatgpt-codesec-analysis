#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           (length == 3U || length == 4U) &&
           memcmp(string, "abbb", length) == 0;
}

static int discard_line_remainder(void)
{
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' &&
           character != '\r' &&
           character != EOF) {
    }

    if (character == '\r') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

        if (character != '\n' && character != EOF) {
            if (ungetc(character, stdin) == EOF) {
                return -1;
            }
        }
    }

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[5];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        puts("No match");
        return EXIT_SUCCESS;
    }

    length = strcspn(input, "\r\n");

    if (input[length] == '\0' && length == sizeof input - 1U) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

        if (character != '\n' && character != '\r' && character != EOF) {
            if (discard_line_remainder() != 0) {
                return EXIT_FAILURE;
            }

            puts("No match");
            return EXIT_SUCCESS;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();

            if (character != '\n' && character != EOF) {
                if (ungetc(character, stdin) == EOF) {
                    return EXIT_FAILURE;
                }
            }
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    } else if (input[length] == '\r') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

        if (character != '\n' && character != EOF) {
            if (ungetc(character, stdin) == EOF) {
                return EXIT_FAILURE;
            }
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';
    puts(matches_pattern(input, length) ? "Match" : "No match");

    return EXIT_SUCCESS;
}