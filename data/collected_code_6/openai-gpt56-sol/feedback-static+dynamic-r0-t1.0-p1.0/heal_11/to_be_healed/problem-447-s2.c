#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#define MAX_LINE_LENGTH 4096U

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return (ch == EOF && ferror(stdin)) ? -1 : 0;
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2U) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        buffer[0] = '\0';
        return -1;
    }

    for (length = 0U; buffer[length] != '\0'; ++length) {
        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return 0;
        }
    }

    if (feof(stdin)) {
        return 0;
    }

    buffer[0] = '\0';
    /* Possible weaknesses found:
     *  Same value in both branches of ternary operator. [duplicateValueTernary]
     */
    return discard_line() == 0 ? -1 : -1;
}

static int read_int64(int64_t *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_LINE_LENGTH];
    char *start;
    char *end;
    intmax_t value;

    if (result == NULL || read_line(buffer, sizeof buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    value = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *result = (int64_t)value;
    return 0;
}

static int read_size(size_t *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_LINE_LENGTH];
    char *start;
    char *end;
    uintmax_t value;

    if (result == NULL || read_line(buffer, sizeof buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return -1;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value == 0U || value > SIZE_MAX) {
        return -1;
    }

    *result = (size_t)value;
    return 0;
}

static int cube_int64(int64_t value, int64_t *result)
{
    int64_t square;

    if (result == NULL ||
        value < -INT64_C(2097152) ||
        value > INT64_C(2097151)) {
        return -1;
    }

    square = value * value;
    *result = square * value;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *values = NULL;
    int exit_status = EXIT_FAILURE;

    if (printf("Enter the number of elements: ") < 0 ||
        fflush(stdout) == EOF) {
        goto cleanup;
    }

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof *values) {
        fprintf(stderr, "Invalid element count.\n");
        goto cleanup;
    }

    values = malloc(count * sizeof *values);
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        goto cleanup;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("Element %zu: ", i + 1U) < 0 ||
            fflush(stdout) == EOF ||
            read_int64(&values[i]) != 0) {
            fprintf(stderr, "Invalid input.\n");
            goto cleanup;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        int64_t cube;

        if (cube_int64(values[i], &cube) != 0) {
            fprintf(stderr,
                    "Cube of element %zu is outside the int64_t range.\n",
                    i + 1U);
            goto cleanup;
        }

        if (printf("%" PRId64 "%c",
                   cube,
                   i + 1U == count ? '\n' : ' ') < 0) {
            goto cleanup;
        }
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(values);
    return exit_status;
}