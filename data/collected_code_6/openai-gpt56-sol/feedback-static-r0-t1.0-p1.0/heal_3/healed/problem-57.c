#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_digits_descending(const void *left, const void *right)
{
    const unsigned char a = *(const unsigned char *)left;
    const unsigned char b = *(const unsigned char *)right;

    return (a < b) - (a > b);
}

static char *largest_number(const char *digits, size_t maximum_length)
{
    size_t length;
    char *result;

    if (digits == NULL || maximum_length == 0U) {
        errno = EINVAL;
        return NULL;
    }

    length = strnlen(digits, maximum_length);
    if (length == 0U || length == maximum_length) {
        errno = EINVAL;
        return NULL;
    }

    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        errno = ENOMEM;
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

int main(int argc, char *argv[])
{
    char *result;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <digits>\n", program_name);
        return EXIT_FAILURE;
    }

    errno = 0;
    result = largest_number(argv[1], SIZE_MAX);

    if (result == NULL) {
        switch (errno) {
        case ENOMEM:
            fputs("Memory allocation failed.\n", stderr);
            break;
        case EOVERFLOW:
            fputs("Input is too large.\n", stderr);
            break;
        default:
            fputs("Input must contain one or more decimal digits.\n", stderr);
            break;
        }

        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        fputs("Output failed.\n", stderr);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}