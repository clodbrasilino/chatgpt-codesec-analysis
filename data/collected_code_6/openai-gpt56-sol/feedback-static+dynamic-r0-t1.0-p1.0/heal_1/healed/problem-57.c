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

static char *largest_number(const char *digits, size_t length)
{
    char *result;

    if (digits == NULL || length == 0U || length == SIZE_MAX) {
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

int main(int argc, char * const argv[])
{
    char *result;
    size_t length;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <digits>\n", program);
        return EXIT_FAILURE;
    }

    length = strnlen(argv[1], SIZE_MAX);
    if (length == SIZE_MAX) {
        fputs("Input is too long or not properly terminated.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    result = largest_number(argv[1], length);
    if (result == NULL) {
        if (errno == ENOMEM) {
            fputs("Memory allocation failed.\n", stderr);
        } else {
            fputs("Input must contain one or more decimal digits.\n", stderr);
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