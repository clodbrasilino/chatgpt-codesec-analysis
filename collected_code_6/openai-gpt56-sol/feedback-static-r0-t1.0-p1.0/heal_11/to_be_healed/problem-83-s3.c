#include <limits.h>
#include <stdio.h>

static unsigned char add_character(unsigned char sum, unsigned char character)
{
    return (unsigned char)((unsigned int)sum + (unsigned int)character);
}

int main(void)
{
    unsigned char sum = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF) {
        if (character == '\n') {
            break;
        }

        sum = add_character(sum, (unsigned char)character);
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (putchar((int)sum) == EOF) {
        return 1;
    }

    if (putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}