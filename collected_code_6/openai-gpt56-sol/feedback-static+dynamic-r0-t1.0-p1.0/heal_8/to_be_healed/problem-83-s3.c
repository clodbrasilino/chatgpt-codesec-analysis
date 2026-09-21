#include <limits.h>
#include <stdio.h>

static unsigned char add_characters(const char *string)
{
    unsigned int sum = 0U;

    while (*string != '\0') {
        sum = (sum + (unsigned char)*string) % (UCHAR_MAX + 1U);
        ++string;
    }

    return (unsigned char)sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    size_t length = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length >= sizeof input - 1U) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            return 1;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (character == EOF && length == 0U) {
        return 0;
    }

    input[length] = '\0';

    if (putchar((int)add_characters(input)) == EOF ||
        putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}