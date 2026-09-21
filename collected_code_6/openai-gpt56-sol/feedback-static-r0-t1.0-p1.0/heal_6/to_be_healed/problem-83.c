#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned char add_characters(const unsigned char *string, size_t length)
{
    uint8_t sum = 0;

    for (size_t i = 0; i < length; ++i) {
        sum = (uint8_t)(sum + string[i]);
    }

    return sum;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };

    unsigned char *input = malloc(MAX_INPUT_LENGTH);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
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
        free(input);
        return EXIT_FAILURE;
    }

    if (length == MAX_INPUT_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character != '\n' && character != EOF) {
            free(input);
            return EXIT_FAILURE;
        }

        if (character == EOF && ferror(stdin)) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    unsigned char result = add_characters(input, length);
    free(input);

    if (printf("%c\n", (int)result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}