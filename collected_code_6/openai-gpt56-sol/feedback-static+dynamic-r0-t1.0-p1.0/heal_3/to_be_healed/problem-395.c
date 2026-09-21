#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static int find_first_non_repeated(const unsigned char *data,
                                   size_t length,
                                   unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t i;

    if (data == NULL || result == NULL) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        ++frequencies[data[i]];
    }

    for (i = 0; i < length; ++i) {
        if (frequencies[data[i]] == 1U) {
            *result = data[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[1024];
    unsigned char result;
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == sizeof input) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            return 1;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (find_first_non_repeated(input, length, &result)) {
        if (putchar((int)result) == EOF || putchar('\n') == EOF) {
            return 1;
        }
    } else if (puts("No non-repeated character found") == EOF) {
        return 1;
    }

    return 0;
}