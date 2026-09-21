#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE_LENGTH 4096U

static int discard_line(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return (ch == EOF && ferror(stdin)) ? -1 : 0;
}

static int read_line(char *buffer, size_t capacity)
{
    char *newline;

    if (buffer == NULL || capacity < 2 || capacity > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return buffer[0] == '\0' ? -1 : 0;
    }

    if (discard_line() != 0) {
        return -1;
    }

    return -1;
}

static int read_int64(int64_t *result)
{
    char *buffer;
    char *start;
    char *end;
    intmax_t value;
    int status = -1;

    if (result == NULL) {
        return -1;
    }

    buffer = malloc(MAX_LINE_LENGTH);
    if (buffer == NULL) {
        return -1;
    }

    if (read_line(buffer, MAX_LINE_LENGTH) != 0) {
        goto cleanup;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    value = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *result = (int64_t)value;
    status = 0;

cleanup:
    free(buffer);
    return status;
}

static int read_size(size_t *result)
{
    char *buffer;
    char *start;
    char *end;
    uintmax_t value;
    int status = -1;

    if (result == NULL) {
        return -1;
    }

    buffer = malloc(MAX_LINE_LENGTH);
    if (buffer == NULL) {
        return -1;
    }

    if (read_line(buffer, MAX_LINE_LENGTH) != 0) {
        goto cleanup;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        goto cleanup;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value == 0 || value > SIZE_MAX) {
        goto cleanup;
    }

    *result = (size_t)value;
    status = 0;

cleanup:
    free(buffer);
    return status;
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

    for (size_t i = 0; i < count; ++i) {
        if (printf("Element %zu: ", i + 1) < 0 ||
            fflush(stdout) == EOF ||
            read_int64(&values[i]) != 0) {
            fprintf(stderr, "Invalid input.\n");
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t cube;

        if (cube_int64(values[i], &cube) != 0) {
            fprintf(stderr,
                    "Cube of element %zu is outside the int64_t range.\n",
                    i + 1);
            goto cleanup;
        }

        if (printf("%" PRId64 "%c",
                   cube,
                   i + 1 == count ? '\n' : ' ') < 0) {
            goto cleanup;
        }
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(values);
    return exit_status;
}