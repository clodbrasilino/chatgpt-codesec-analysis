#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int find_first_non_repeated(const unsigned char *data,
                                   size_t length,
                                   unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t i;

    if (result == NULL || (data == NULL && length != 0)) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        if (frequencies[data[i]] < SIZE_MAX) {
            ++frequencies[data[i]];
        }
    }

    for (i = 0; i < length; ++i) {
        if (frequencies[data[i]] == 1) {
            *result = data[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char result = 0;
    int character;
    int status = EXIT_SUCCESS;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_input;

            if (capacity == 0) {
                new_capacity = 1024;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    status = EXIT_FAILURE;
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length] = (unsigned char)character;
        ++length;
    }

    if (ferror(stdin)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (find_first_non_repeated(input, length, &result)) {
        if (putchar((int)result) == EOF || putchar('\n') == EOF) {
            status = EXIT_FAILURE;
        }
    } else if (puts("No non-repeated character found") == EOF) {
        status = EXIT_FAILURE;
    }

cleanup:
    free(input);
    return status;
}