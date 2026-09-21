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

        while (count > 0U) {
            result[position++] = (char)('0' + digit);
            --count;
        }
    }

    result[position] = '\0';
    return result;
}

static int discard_remainder(int current)
{
    int ch = current;

    for (;;) {
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
            ch = fgetc(stdin);

            if (ch == EOF) {
                return ferror(stdin) ? -1 : 0;
            }

            if (ch != '\n' && ungetc(ch, stdin) == EOF) {
                return -1;
            }

            return 0;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }
}

static int read_digits(char **digits, size_t *length)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[MAX_DIGITS + 2U];
    char *buffer;
    size_t used = 0U;
    int terminated = 0;

    if (digits == NULL || length == NULL) {
        errno = EINVAL;
        return -1;
    }

    *digits = NULL;
    *length = 0U;

    if (fgets(line, (int)sizeof line, stdin) == NULL) {
        if (ferror(stdin)) {
            errno = EIO;
        } else {
            errno = EINVAL;
        }
        return -1;
    }

    while (line[used] != '\0') {
        unsigned char ch = (unsigned char)line[used];

        if (ch == (unsigned char)'\n') {
            terminated = 1;
            break;
        }

        if (ch == (unsigned char)'\r') {
            int next;

            terminated = 1;
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    errno = EIO;
                    return -1;
                }
            } else if (next != '\n' && ungetc(next, stdin) == EOF) {
                errno = EIO;
                return -1;
            }

            break;
        }

        if (ch < (unsigned char)'0' || ch > (unsigned char)'9') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            if (!terminated && discard_remainder(fgetc(stdin)) != 0) {
                errno = EIO;
            } else {
                errno = EINVAL;
            }
            return -1;
        }

        ++used;
    }

    if (!terminated && line[used] == '\0' && !feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stdin);

        if (next != EOF) {
            if (discard_remainder(next) != 0) {
                errno = EIO;
            } else {
                errno = EOVERFLOW;
            }
            return -1;
        }

        if (ferror(stdin)) {
            errno = EIO;
            return -1;
        }
    }

    if (used == 0U) {
        errno = EINVAL;
        return -1;
    }

    buffer = malloc(used + 1U);
    if (buffer == NULL) {
        errno = ENOMEM;
        return -1;
    }

    for (size_t i = 0U; i < used; ++i) {
        buffer[i] = line[i];
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