#include <stdbool.h>
#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'EXIT_FAILURE' is defined in header '<stdlib.h>'; this is probably fixable by adding '#include <stdlib.h>'
  */

static bool matches(const char *string)
{
    return string != NULL &&
           (strcmp(string, "a") == 0 || strcmp(string, "ab") == 0);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[3];
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length < sizeof(input) - 1) {
            input[length++] = (char)character;
        } else {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            if (ferror(stdin)) {
                perror("fgetc");
            } else {
                fputs("Input is too long\n", stderr);
            }

            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  'EXIT_FAILURE' undeclared (first use in this function)
             *  use of undeclared identifier 'EXIT_FAILURE'
             */
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        perror("fgetc");
        /* Possible weaknesses found:
         *  use of undeclared identifier 'EXIT_FAILURE'
         */
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        /* Possible weaknesses found:
         *  'EXIT_SUCCESS' is defined in header '<stdlib.h>'; this is probably fixable by adding '#include <stdlib.h>'
         *  'EXIT_SUCCESS' undeclared (first use in this function)
         *  use of undeclared identifier 'EXIT_SUCCESS'
         */
        return EXIT_SUCCESS;
    }

    input[length] = '\0';
    puts(matches(input) ? "Match" : "No match");

    /* Possible weaknesses found:
     *  use of undeclared identifier 'EXIT_SUCCESS'
     */
    return EXIT_SUCCESS;
}