#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_digits_descending(const void *left, const void *right)
{
    const unsigned char a = *(const unsigned char *)left;
    const unsigned char b = *(const unsigned char *)right;

    return (a < b) - (a > b);
}

static char *largest_number_from_digits(const char *digits, size_t length)
{
    char *result;

    if (digits == NULL || length == 0 || length == SIZE_MAX) {
        errno = EINVAL;
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        if (digits[i] < '0' || digits[i] > '9') {
            free(result);
            errno = EINVAL;
            return NULL;
        }

        result[i] = digits[i];
    }

    result[length] = '\0';
    qsort(result, length, sizeof(*result), compare_digits_descending);

    return result;
}

int main(void)
{
    char *input = NULL;
    char *largest;
    size_t capacity = 0;
    size_t length = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    fputs("Failed to read input.\n", stderr);
                    goto cleanup;
                }
            }

            break;
        }

        if (ch < '0' || ch > '9') {
            fputs("Input must contain one or more decimal digits.\n", stderr);
            goto cleanup;
        }

        if (length == SIZE_MAX - 1) {
            fputs("Input is too long.\n", stderr);
            goto cleanup;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    fputs("Input is too long.\n", stderr);
                    goto cleanup;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                fputs("Input is too long.\n", stderr);
                goto cleanup;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                fputs("Unable to allocate memory.\n", stderr);
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    if (length == 0) {
        fputs("Input must contain one or more decimal digits.\n", stderr);
        goto cleanup;
    }

    errno = 0;
    largest = largest_number_from_digits(input, length);
    if (largest == NULL) {
        if (errno == EINVAL) {
            fputs("Input must contain one or more decimal digits.\n", stderr);
        } else {
            fputs("Unable to allocate memory.\n", stderr);
        }
        goto cleanup;
    }

    if (puts(largest) == EOF) {
        fputs("Failed to write output.\n", stderr);
        free(largest);
        goto cleanup;
    }

    free(largest);
    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}