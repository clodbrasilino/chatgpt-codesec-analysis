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
    while ((character = getchar()) != EOF) {
        if (character == '\n') {
            break;
        }

        sum = (sum + (unsigned char)character) % (UCHAR_MAX + 1U);
    }

    if (character == EOF && ferror(stdin)) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char result_string[2];
    result_string[0] = (unsigned char)sum;
    result_string[1] = '\0';

    const unsigned char result = add_characters(result_string);

    if (putchar((int)result) == EOF) {
        return 1;
    }

    if (putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}