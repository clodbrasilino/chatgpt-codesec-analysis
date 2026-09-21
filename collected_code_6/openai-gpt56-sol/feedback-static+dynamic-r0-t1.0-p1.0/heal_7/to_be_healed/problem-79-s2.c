#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

static bool has_odd_length(size_t length)
{
    return (length & 1U) != 0U;
}

int main(void)
{
    size_t length = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'SIZE_MAX'
         *  'SIZE_MAX' undeclared (first use in this function)
         */
        if (length == SIZE_MAX) {
            return 1;
        }
        ++length;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        return 1;
    }

    if (puts(has_odd_length(length) ? "Odd" : "Even") == EOF) {
        return 1;
    }

    return 0;
}