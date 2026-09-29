#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 >= size) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));
            return -1;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
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
        parsed > SIZE_MAX) {
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

static int sum_absolute_differences(int64_t *values, size_t count,
                                    uint64_t *result)
{
    __int128 prefix_sum = 0;
    __int128 total = 0;

    if ((values == NULL && count != 0) || result == NULL) {
        return -1;
    }

    qsort(values, count, sizeof(*values), compare_int64);

    for (size_t i = 0; i < count; ++i) {
        __int128 contribution =
            (__int128)values[i] * (__int128)i - prefix_sum;

        if (contribution < 0 || total + contribution > UINT64_MAX) {
            return -1;
        }

        total += contribution;
        prefix_sum += (__int128)values[i];
    }

    *result = (uint64_t)total;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *values;
    uint64_t result;

    if (read_size(&count) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count == 0) {
        puts("0");
        return EXIT_SUCCESS;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Array size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&values[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (sum_absolute_differences(values, count, &result) != 0) {
        fputs("Result is out of range\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(values);
    return EXIT_SUCCESS;
}