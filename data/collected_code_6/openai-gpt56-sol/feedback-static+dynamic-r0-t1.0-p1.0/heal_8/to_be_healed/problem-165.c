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

        if (character >= (unsigned char)'a' &&
            character <= (unsigned char)'z' &&
            (size_t)(character - (unsigned char)'a') == i) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

        if (character == EOF) {
            if (ferror(stdin) || length == 0) {
                goto cleanup;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\0') {
            goto cleanup;
        }

        if (length == SIZE_MAX - 1) {
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                goto cleanup;
            }

            resized = realloc(string, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            string = resized;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)character;
    }

    if (capacity <= length) {
        char *resized;

        if (length == SIZE_MAX) {
            goto cleanup;
        }

        resized = realloc(string, length + 1);
        if (resized == NULL) {
            goto cleanup;
        }

        string = resized;
    }

    string[length] = '\0';

    if (printf("%zu\n", count_matching_positions(string)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(string);
    return status;
}