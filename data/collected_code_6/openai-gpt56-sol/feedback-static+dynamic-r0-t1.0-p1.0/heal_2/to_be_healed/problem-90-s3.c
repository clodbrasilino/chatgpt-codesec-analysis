#include <ctype.h>
#include <stdio.h>

int main(void)
{
    size_t longest = 0U;
    size_t current = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (isalnum((unsigned char)ch) != 0) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0U;
        }
    }

    if (ferror(stdin) != 0) {
        return 1;
    }

    if (printf("%zu\n", longest) < 0) {
        return 1;
    }

    return 0;
}