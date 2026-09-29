#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 4095U

static char *largest_number_from_digits(const char *digits, size_t length)
{
    size_t counts[10] = {0U};
    char *result;
    size_t position = 0U;
    size_t i;
    int digit;

    if (digits == NULL || length == 0U || length > MAX_DIGITS) {
        errno = EINVAL;
        return NULL;
    }

    for (i = 0U; i < length; ++i) {
        unsigned char ch = (unsigned char)digits[i];

        if (ch < (unsigned char)'0' || ch > (unsigned char)'9') {
            errno = EINVAL;
            return NULL;
        }

        ++counts[ch - (unsigned char)'0'];
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (digit = 9; digit >= 0; --digit) {
        size_t count = counts[(size_t)digit];

        while (count != 0U) {
            result[position++] = (char)('0' + digit);
            --count;
        }
    }

    result[position] = '\0';
    return result;
}

static int discard_line(void)
{
    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            return ferror(stdin) ? -1 : 0;
        }

        if (ch == '\n') {
            return 0;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next == EOF) {
                return ferror(stdin) ? -1 : 0;
            }

            if (next != '\n' && ungetc(next, stdin) == EOF) {
                return -1;
            }

            return 0;
        }
    }
}

static int read_digits(char **digits, size_t *length)
{
    char *buffer;
    size_t used = 0U;

    if (digits == NULL || length == NULL) {
        errno = EINVAL;
        return -1;
    }

    *digits = NULL;
    *length = 0U;

    buffer = malloc(MAX_DIGITS + 1U);
    if (buffer == NULL) {
        errno = ENOMEM;
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n' || ch == '\r') {
            if (ch == '\r') {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                int next = fgetc(stdin);

                if (next == EOF) {
                    if (ferror(stdin)) {
                        free(buffer);
                        return -1;
                    }
                } else if (next != '\n' && ungetc(next, stdin) == EOF) {
                    free(buffer);
                    return -1;
                }
            }
            break;
        }

        if (used >= MAX_DIGITS) {
            if (discard_line() != 0) {
                free(buffer);
                return -1;
            }

            free(buffer);
            errno = EOVERFLOW;
            return -1;
        }

        if (ch < '0' || ch > '9') {
            if (discard_line() != 0) {
                free(buffer);
                return -1;
            }

            free(buffer);
            errno = EINVAL;
            return -1;
        }

        buffer[used++] = (char)ch;
    }

    if (used == 0U) {
        free(buffer);
        errno = EINVAL;
        return -1;
    }

    buffer[used] = '\0';
    *digits = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *digits = NULL;
    char *largest;
    size_t length = 0U;

    errno = 0;
    if (read_digits(&digits, &length) != 0) {
        if (errno == EOVERFLOW) {
            fputs("Input is too long.\n", stderr);
        } else if (errno == EINVAL) {
            fputs("Input must contain one or more decimal digits.\n", stderr);
        } else if (errno == ENOMEM) {
            fputs("Unable to allocate memory.\n", stderr);
        } else {
            fputs("Failed to read input.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    largest = largest_number_from_digits(digits, length);
    free(digits);

    if (largest == NULL) {
        if (errno == EINVAL) {
            fputs("Input must contain one or more decimal digits.\n", stderr);
        } else {
            fputs("Unable to allocate memory.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    if (puts(largest) == EOF) {
        free(largest);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(largest);

    if (fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}