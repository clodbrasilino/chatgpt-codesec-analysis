#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    size_t longest = 0;
    size_t current = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (isalnum((unsigned char)ch)) {
            if (current == SIZE_MAX) {
                return 1;
            }

            ++current;

            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
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