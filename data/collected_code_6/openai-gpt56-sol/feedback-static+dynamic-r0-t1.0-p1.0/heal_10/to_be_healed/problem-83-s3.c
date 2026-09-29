#include <limits.h>
#include <stdio.h>

static unsigned char add_characters(const unsigned char *data, size_t length)
{
    unsigned int sum = 0U;

    for (size_t i = 0U; i < length; ++i) {
        sum = (sum + data[i]) % (UCHAR_MAX + 1U);
    }

    return (unsigned char)sum;
}

int main(void)
{
    unsigned int sum = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        sum = (sum + (unsigned char)character) % (UCHAR_MAX + 1U);
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (character == EOF && sum == 0U) {
        return 0;
    }

    if (putchar((int)(unsigned char)sum) == EOF || putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}