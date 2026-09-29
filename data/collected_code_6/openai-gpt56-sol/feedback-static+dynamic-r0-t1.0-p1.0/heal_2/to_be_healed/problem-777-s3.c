#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_token(char *buffer, size_t size)
{
    int c;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return -1;
    }

    while (c != EOF && !isspace((unsigned char)c)) {
        if (length + 1 >= size) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                c = getchar();
            } while (c != EOF && !isspace((unsigned char)c));
            return -1;
        }

        buffer[length++] = (char)c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    }

    buffer[length] = '\0';
    return 0;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0 ||
        buffer[0] == '-') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int sum_non_repeated(const int64_t *array, size_t length, int64_t *sum)
{
    int64_t *copy;
    int64_t result = 0;
    size_t i = 0;

    if (array == NULL || sum == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        return -1;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (size_t index = 0; index < length; ++index) {
        copy[index] = array[index];
    }

    qsort(copy, length, sizeof(*copy), compare_int64);

    while (i < length) {
        size_t j = i + 1;

        while (j < length && copy[j] == copy[i]) {
            ++j;
        }

        if (j - i == 1) {
            if ((copy[i] > 0 && result > INT64_MAX - copy[i]) ||
                (copy[i] < 0 && result < INT64_MIN - copy[i])) {
                free(copy);
                return -1;
            }

            result += copy[i];
        }

        i = j;
    }

    free(copy);
    *sum = result;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t sum;

    if (read_size(&length) != 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (sum_non_repeated(array, length, &sum) != 0) {
        fputs("Unable to calculate sum\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}