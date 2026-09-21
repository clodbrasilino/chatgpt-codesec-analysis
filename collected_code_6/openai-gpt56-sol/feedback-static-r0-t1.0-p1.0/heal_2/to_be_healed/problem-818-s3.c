#include <ctype.h>
#include <stdio.h>

int main(void)
{
    size_t count = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (islower((unsigned char)character) != 0) {
            ++count;
        }
    }

    if (ferror(stdin) != 0) {
        return 1;
    }

    if (printf("%zu\n", count) < 0) {
        return 1;
    }

    return 0;
}