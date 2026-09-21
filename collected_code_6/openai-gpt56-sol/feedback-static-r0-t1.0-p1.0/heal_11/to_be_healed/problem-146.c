#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int print_ascii_values(const unsigned char *string, size_t length)
{
    if (string == NULL && length != 0U) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf("%u\n", (unsigned int)string[i]) < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    unsigned char *string = malloc((size_t)MAX_INPUT_LENGTH);
    size_t length = 0U;
    int result = EXIT_FAILURE;
    int character;

    if (string == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= (size_t)MAX_INPUT_LENGTH) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            } while (character != EOF && character != '\n');

            if (character == EOF && ferror(stdin)) {
                perror("fgetc");
            } else {
                fprintf(stderr, "Input exceeds maximum length\n");
            }

            goto cleanup;
        }

        string[length++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        perror("fgetc");
        goto cleanup;
    }

    if (print_ascii_values(string, length) != 0) {
        fprintf(stderr, "Output error\n");
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(string);
    return result;
}