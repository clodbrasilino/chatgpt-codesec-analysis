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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[6];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        puts("No match");
        return EXIT_SUCCESS;
    }

    length = strcspn(input, "\r\n");

    if (input[length] == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            ungetc(character, stdin);
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    } else if (input[length] == '\0' && !feof(stdin)) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = fgetc(stdin);
        } while (character != '\n' && character != '\r' && character != EOF);

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = fgetc(stdin);

            if (character != '\n' && character != EOF) {
                ungetc(character, stdin);
            }
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        puts("No match");
        return EXIT_SUCCESS;
    }

    input[length] = '\0';

    puts(matches_pattern(input, length) ? "Match" : "No match");

    return EXIT_SUCCESS;
}