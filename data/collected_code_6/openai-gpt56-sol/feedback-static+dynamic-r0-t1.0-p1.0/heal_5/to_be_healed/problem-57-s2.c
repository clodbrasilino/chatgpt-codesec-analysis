#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 4095U

static char *largest_number_from_digits(const char *digits, size_t length)
{
    size_t counts[10] = {0};
    char *result;
    size_t position = 0U;

    if (digits == NULL || length == 0U || length > MAX_DIGITS) {
        errno = EINVAL;
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        unsigned char ch = (unsigned char)digits[i];

        if (ch < (unsigned char)'0' || ch > (unsigned char)'9') {
            errno = EINVAL;
            return NULL;
        }

        ++counts[ch - (unsigned char)'0'];
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (int digit = 9; digit >= 0; --digit) {
        while (counts[digit] > 0U) {
            result[position++] = (char)('0' + digit);
            --counts[digit];
        }
    }

    result[position] = '\0';
    return result;
}

static int read_digits(char **digits, size_t *length)
{
    char *buffer;
    size_t used = 0U;
    int ch;

    if (digits == NULL || length == NULL) {
        errno = EINVAL;
        return -1;
    }

    buffer = malloc(MAX_DIGITS + 1U);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
        if (used >= MAX_DIGITS) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && ch != '\n' && ch != '\r');

            free(buffer);

            if (ferror(stdin)) {
                return -1;
            }

            errno = EOVERFLOW;
            return -1;
        }

        if (ch < '0' || ch > '9') {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && ch != '\n' && ch != '\r');

            free(buffer);

            if (ferror(stdin)) {
                return -1;
            }

            errno = EINVAL;
            return -1;
        }

        buffer[used++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(buffer);
        return -1;
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
    char *largest = NULL;
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
    return EXIT_SUCCESS;
}