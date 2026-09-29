#include <ctype.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

int main(void)
{
    size_t longest = 0U;
    size_t current = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (isalnum((unsigned char)ch)) {
            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  use of undeclared identifier 'SIZE_MAX'
             *  'SIZE_MAX' undeclared (first use in this function)
             */
            if (current < SIZE_MAX) {
                ++current;
            }

            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0U;
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (printf("%zu\n", longest) < 0) {
        return 1;
    }

    return 0;
}