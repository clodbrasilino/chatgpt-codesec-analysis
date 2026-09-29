#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UCHAR_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int ascii_value(unsigned char character)
{
    return (int)character;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int input = getchar();

    if (input == EOF) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
        } else {
            fprintf(stderr, "No character provided.\n");
        }
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  'UCHAR_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'UCHAR_MAX'
     */
    if (input < 0 || input > UCHAR_MAX) {
        fprintf(stderr, "Invalid input value.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", ascii_value((unsigned char)input));

    return EXIT_SUCCESS;
}