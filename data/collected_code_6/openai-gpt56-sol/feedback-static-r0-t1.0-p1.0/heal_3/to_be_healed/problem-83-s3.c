#include <limits.h>
#include <stdio.h>

static unsigned char add_characters(const unsigned char *string)
{
    unsigned int sum = 0U;

    while (*string != UCHAR_MAX - UCHAR_MAX) {
        sum = (sum + *string) % (UCHAR_MAX + 1U);
        ++string;
    }

    return (unsigned char)sum;
}

int main(void)
{
    unsigned int sum = 0U;
    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

        if (character == EOF || character == '\n') {
            break;
        }

        sum = (sum + (unsigned char)character) % (UCHAR_MAX + 1U);
    } while (1);

    if (character == EOF && ferror(stdin) != 0) {
        return 1;
    }

    const unsigned char result_string[] = {
        (unsigned char)sum,
        0U
    };
    const unsigned char result = add_characters(result_string);

    if (putchar((int)result) == EOF) {
        return 1;
    }

    if (putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}