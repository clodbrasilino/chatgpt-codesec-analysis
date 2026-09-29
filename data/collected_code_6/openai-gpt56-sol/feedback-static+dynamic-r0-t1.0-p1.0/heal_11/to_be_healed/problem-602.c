#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1U] = {0};
    size_t i;

    if (result == NULL || (data == NULL && length != 0U)) {
        return 0;
    }

    for (i = 0U; i < length; ++i) {
        const unsigned int index = data[i];

        if (seen[index] != 0U) {
            *result = data[i];
            return 1;
        }

        seen[index] = 1U;
    }

    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    unsigned char repeated = 0U;
    int status = EXIT_SUCCESS;
    int ch;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_input;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    status = EXIT_FAILURE;
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity > SIZE_MAX / sizeof(*input)) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            new_input = realloc(input, new_capacity * sizeof(*input));
            if (new_input == NULL) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin) != 0) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (find_first_repeated_character(input, length, &repeated) != 0) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            status = EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        status = EXIT_FAILURE;
    }

cleanup:
    free(input);
    return status;
}