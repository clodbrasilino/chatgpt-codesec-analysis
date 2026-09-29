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

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ch == '\n' || feof(stdin);
}

static int read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2 || capacity > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return 0;
    }

    size_t length = 0;

    while (length < capacity && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length < capacity && buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (length < capacity && buffer[length] == '\0' && feof(stdin)) {
        return 1;
    }

    (void)discard_line();
    return 0;
}

static char *allocate_input_buffer(void)
{
    return malloc(MAX_LINE_LENGTH);
}

static int read_size(size_t *value)
{
    if (value == NULL) {
        return 0;
    }

    char *buffer = allocate_input_buffer();

    if (buffer == NULL) {
        return 0;
    }

    if (!read_line(buffer, MAX_LINE_LENGTH)) {
        free(buffer);
        return 0;
    }

    char *start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed > (uintmax_t)SIZE_MAX) {
        free(buffer);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int read_int64(int64_t *value)
{
    if (value == NULL) {
        return 0;
    }

    char *buffer = allocate_input_buffer();

    if (buffer == NULL) {
        return 0;
    }

    if (!read_line(buffer, MAX_LINE_LENGTH)) {
        free(buffer);
        return 0;
    }

    char *start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        free(buffer);
        return 0;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (errno == ERANGE || end == start ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        free(buffer);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static int minimum_to_make_sum_even(const int64_t *array, size_t length,
                                    int64_t *result)
{
    if (result == NULL || (array == NULL && length != 0)) {
        return 0;
    }

    uint64_t parity = 0;

    for (size_t i = 0; i < length; ++i) {
        parity ^= (uint64_t)array[i] & UINT64_C(1);
    }

    *result = (int64_t)parity;
    return 1;
}

int main(void)
{
    size_t length;

    if (!read_size(&length) || length > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *array = NULL;

    if (length != 0) {
        array = malloc(length * sizeof *array);

        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            if (!read_int64(&array[i])) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    int64_t minimum;

    if (!minimum_to_make_sum_even(array, length, &minimum)) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", minimum) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}