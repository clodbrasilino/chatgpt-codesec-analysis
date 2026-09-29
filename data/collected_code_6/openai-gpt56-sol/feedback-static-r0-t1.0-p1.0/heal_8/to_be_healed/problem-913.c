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
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (character != '\r') {
            last_character = character;
        } else {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next_character = fgetc(stdin);

            if (next_character == EOF) {
                if (ferror(stdin)) {
                    return EXIT_FAILURE;
                }
                last_character = EOF;
                break;
            }

            if (next_character == '\n') {
                last_character = EOF;
                break;
            }

            last_character = '\r';
            character = next_character;

            if (character != '\r') {
                last_character = character;
            }
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (puts(ends_with_number(last_character) ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}