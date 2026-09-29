#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int compare_digits_descending(const void *left, const void *right)
{
    const unsigned char a = *(const unsigned char *)left;
    const unsigned char b = *(const unsigned char *)right;

    return (a < b) - (a > b);
}

static char *largest_number_from_digits(const char *digits)
{
    size_t length;
    char *result;

    if (digits == NULL) {
        errno = EINVAL;
        return NULL;
    }

    length = strlen(digits);
    if (length == 0U || length == SIZE_MAX) {
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
    qsort(result, length, sizeof(result[0]), compare_digits_descending);

    return result;
}

int main(void)
{
    char input[4096];
    char *largest;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = strcspn(input, "\r\n");

    if (input[length] == '\0' && length == sizeof(input) - 1U) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';
    errno = 0;
    largest = largest_number_from_digits(input);

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