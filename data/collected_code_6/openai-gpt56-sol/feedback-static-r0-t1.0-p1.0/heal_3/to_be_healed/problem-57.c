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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *const argv[const])
{
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <digits>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    result = largest_number(argv[1], SIZE_MAX);
    if (result == NULL) {
        if (errno == ENOMEM) {
            fputs("Memory allocation failed.\n", stderr);
        } else if (errno == EOVERFLOW) {
            fputs("Input is too large.\n", stderr);
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