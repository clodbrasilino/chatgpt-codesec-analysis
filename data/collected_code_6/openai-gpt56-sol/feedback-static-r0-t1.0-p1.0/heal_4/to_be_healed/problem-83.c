#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned char add_characters(const unsigned char *string, size_t length)
{
    unsigned int sum = 0U;

    for (size_t i = 0U; i < length; ++i) {
        sum = (sum + string[i]) & UINT8_MAX;
    }

    return (unsigned char)sum;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[MAX_INPUT_LENGTH];
    size_t length = 0U;
    int character;

    while (length < MAX_INPUT_LENGTH &&
           /* Possible weaknesses found:
            * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
            */
           (character = fgetc(stdin)) != EOF &&
           character != '\n') {
        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (length == MAX_INPUT_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character != '\n' && character != EOF) {
            return EXIT_FAILURE;
        }
        if (character == EOF && ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    unsigned char result = add_characters(input, length);

    if (printf("%c\n", (int)result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}