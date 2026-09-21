#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int read_line(char *buffer, size_t size)
{
    int ch;
    size_t length = 0U;

    if (buffer == NULL || size < 2U) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U >= size) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return -1;
        }
        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        return -1;
    }

    buffer[length] = '\0';
    return 0;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed == 0U ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
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
    char buffer[128];
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (errno == ERANGE || end == start ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int add_consecutive(const int64_t *numbers, size_t count, int64_t *sum)
{
    int64_t total = 0;

    if (numbers == NULL || sum == NULL || count == 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if ((numbers[i] > 0 && total > INT64_MAX - numbers[i]) ||
            (numbers[i] < 0 && total < INT64_MIN - numbers[i])) {
            return -1;
        }

        total += numbers[i];
    }

    *sum = total;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *numbers;
    int64_t sum;

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof(*numbers)) {
        fputs("Invalid list size.\n", stderr);
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (read_int64(&numbers[i]) != 0) {
            fputs("Invalid number.\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (add_consecutive(numbers, count, &sum) != 0) {
        fputs("Unable to calculate sum.\n", stderr);
        free(numbers);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", sum);
    free(numbers);
    return EXIT_SUCCESS;
}