#include <limits.h>
#include <stdio.h>

static unsigned char add_characters(const unsigned char *string, size_t length)
{
    unsigned int sum = 0U;
    size_t index;

    for (index = 0U; index < length; ++index) {
        sum = (sum + string[index]) % (UCHAR_MAX + 1U);
    }

    return (unsigned char)sum;
}

int main(void)
{
    unsigned int sum = 0U;
    int character;
    unsigned char result;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        sum = (sum + (unsigned char)character) % (UCHAR_MAX + 1U);
    }

    if (ferror(stdin)) {
        return 1;
    }

    /* Possible weaknesses found:
     *  Value stored to 'result' is never read [deadcode.DeadStores]
     *  result is assigned
     */
    result = add_characters((const unsigned char *)&sum, 0U);
    /* Possible weaknesses found:
     *  Variable 'result' is reassigned a value before the old one has been used. [redundantAssignment]
     *  result is overwritten
     */
    result = (unsigned char)sum;

    if (putchar((int)result) == EOF) {
        return 1;
    }

    if (putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}