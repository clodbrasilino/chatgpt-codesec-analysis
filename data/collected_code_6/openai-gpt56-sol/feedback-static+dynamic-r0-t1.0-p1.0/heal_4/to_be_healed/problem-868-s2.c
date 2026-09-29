#include <ctype.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

static int last_word_length(FILE *stream, size_t *length)
{
    size_t current_length = 0;
    size_t last_length = 0;
    int ch;

    if (stream == NULL || length == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (isspace((unsigned char)ch)) {
            if (current_length != 0) {
                last_length = current_length;
                current_length = 0;
            }
        } else {
            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  use of undeclared identifier 'SIZE_MAX'
             *  'SIZE_MAX' undeclared (first use in this function)
             */
            if (current_length == SIZE_MAX) {
                return -1;
            }
            ++current_length;
        }
    }

    if (ferror(stream)) {
        return -1;
    }

    if (current_length != 0) {
        last_length = current_length;
    }

    *length = last_length;
    return 0;
}

int main(void)
{
    size_t length;

    if (last_word_length(stdin, &length) != 0) {
        return 1;
    }

    if (printf("%zu\n", length) < 0) {
        return 1;
    }

    return 0;
}