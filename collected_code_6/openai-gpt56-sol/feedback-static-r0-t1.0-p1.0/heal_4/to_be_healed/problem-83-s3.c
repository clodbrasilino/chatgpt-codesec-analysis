#include <limits.h>
#include <stdio.h>

static unsigned char add_characters(const unsigned char *string)
{
    unsigned int sum = 0U;

    while (*string != '\0') {
        sum = (sum + *string) % (UCHAR_MAX + 1U);
        ++string;
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
    while ((character = getchar()) != EOF && character != '\n') {
        sum = (sum + (unsigned char)character) % (UCHAR_MAX + 1U);
    }

    if (character == EOF && ferror(stdin)) {
        return 1;
    }

    const unsigned char result_string[] = {
        (unsigned char)sum,
        '\0'
    };
    const unsigned char result = add_characters(result_string);

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}