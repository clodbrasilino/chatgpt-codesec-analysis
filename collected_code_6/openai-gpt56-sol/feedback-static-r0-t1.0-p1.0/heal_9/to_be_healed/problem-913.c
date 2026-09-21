#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool ends_with_number(int character)
{
    return character != EOF && isdigit((unsigned char)character) != 0;
}

int main(void)
{
    int character;
    int last_character = EOF;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next_character = fgetc(stdin);

            if (next_character == EOF) {
                if (ferror(stdin)) {
                    return EXIT_FAILURE;
                }
                break;
            }

            if (next_character == '\n') {
                break;
            }

            /* Possible weaknesses found:
             *  last_character is assigned
             *  Value stored to 'last_character' is never read [deadcode.DeadStores]
             */
            last_character = '\r';
            character = next_character;
        }

        /* Possible weaknesses found:
         *  Variable 'last_character' is reassigned a value before the old one has been used. [redundantAssignment]
         *  last_character is overwritten
         */
        last_character = character;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (puts(ends_with_number(last_character) ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}