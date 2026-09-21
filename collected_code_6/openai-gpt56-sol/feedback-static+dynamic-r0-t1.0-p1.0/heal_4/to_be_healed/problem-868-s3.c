#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

static int length_of_last_word(FILE *stream, size_t *result)
{
    size_t last_length = 0;
    size_t current_length = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (isspace((unsigned char)ch) != 0) {
            if (current_length > 0) {
                last_length = current_length;
                current_length = 0;
            }
        } else {
            if (current_length == SIZE_MAX) {
                return -1;
            }
            current_length++;
        }
    }

    *result = current_length > 0 ? current_length : last_length;
    return 0;
}

int main(void)
{
    size_t result = 0;

    if (length_of_last_word(stdin, &result) != 0) {
        return 1;
    }

    if (printf("%zu\n", result) < 0) {
        return 1;
    }

    return 0;
}