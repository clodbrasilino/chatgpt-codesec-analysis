#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 4095U

static int compare_digits_descending(const void *left, const void *right)
{
    const unsigned char a = *(const unsigned char *)left;
    const unsigned char b = *(const unsigned char *)right;

    return (a < b) - (a > b);
}

static char *largest_number_from_digits(const char *digits, size_t length)
{
    char *result;

    if (digits == NULL || length == 0U || length > MAX_DIGITS) {
        errno = EINVAL;
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (digits[i] < '0' || digits[i] > '9') {
            free(result);
            errno = EINVAL;
            return NULL;
        }

        result[i] = digits[i];
    }

    result[length] = '\0';
    qsort(result, length, sizeof result[0], compare_digits_descending);

    return result;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_DIGITS + 1U];
    char *largest;
    size_t length = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
        if (length == MAX_DIGITS) {
            if (discard_line() != 0) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }
            return EXIT_FAILURE;
        }

        input[length++] = (char)ch;
    }

    if (ch == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stdin);

        if (next != '\n' && next != EOF) {
            if (ungetc(next, stdin) == EOF) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    errno = 0;
    largest = largest_number_from_digits(input, length);
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