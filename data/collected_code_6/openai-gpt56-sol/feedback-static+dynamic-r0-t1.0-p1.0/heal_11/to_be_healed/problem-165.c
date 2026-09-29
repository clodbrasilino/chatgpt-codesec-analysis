#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_matching_positions(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (character >= (unsigned char)'A' &&
            character <= (unsigned char)'Z') {
            character = (unsigned char)(character - (unsigned char)'A' +
                                        (unsigned char)'a');
        }

        if (i < 26 &&
            character >= (unsigned char)'a' &&
            character <= (unsigned char)'z' &&
            (size_t)(character - (unsigned char)'a') == i) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };
    char *string = malloc(MAX_INPUT_LENGTH + 1U);
    size_t length = 0;
    int status = EXIT_FAILURE;

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(string, MAX_INPUT_LENGTH + 1U, stdin) == NULL) {
        goto cleanup;
    }

    while (string[length] != '\0' && string[length] != '\n') {
        ++length;
    }

    if (string[length] == '\n') {
        string[length] = '\0';
    } else if (length == MAX_INPUT_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

        if (character != '\n' && character != EOF) {
            goto cleanup;
        }

        if (character == EOF && ferror(stdin)) {
            goto cleanup;
        }
    }

    if (printf("%zu\n", count_matching_positions(string)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(string);
    return status;
}