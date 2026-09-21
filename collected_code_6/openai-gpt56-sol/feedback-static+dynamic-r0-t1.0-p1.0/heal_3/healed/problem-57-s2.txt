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

static int discard_remaining_line(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char input[MAX_DIGITS + 2U];
    char *largest;
    size_t length;
    char *line_end;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input must contain one or more decimal digits.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    for (line_end = input;
         *line_end != '\0' && *line_end != '\n' && *line_end != '\r';
         ++line_end) {
    }

    if (*line_end == '\0') {
        length = (size_t)(line_end - input);

        if (length > MAX_DIGITS) {
            if (discard_remaining_line() != 0) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }
            return EXIT_FAILURE;
        }

        if (!feof(stdin)) {
            if (discard_remaining_line() != 0) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }
            return EXIT_FAILURE;
        }
    } else {
        length = (size_t)(line_end - input);
        *line_end = '\0';
    }

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