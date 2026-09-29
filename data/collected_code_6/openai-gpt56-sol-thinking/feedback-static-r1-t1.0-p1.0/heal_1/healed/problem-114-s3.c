#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct {
    int first;
    int second;
    size_t frequency;
} Tuple;

bool assign_tuple_frequencies(Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL && count != 0U) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        size_t frequency = 0U;

        for (j = 0U; j < count; ++j) {
            if (tuples[i].first == tuples[j].first &&
                tuples[i].second == tuples[j].second) {
                ++frequency;
            }
        }

        tuples[i].frequency = frequency;
    }

    return true;
}

static bool read_line(char **buffer, size_t *capacity)
{
    ssize_t result;
    size_t length;

    if (buffer == NULL || capacity == NULL) {
        return false;
    }

    result = getline(buffer, capacity, stdin);
    if (result < 0) {
        return false;
    }

    length = (size_t)result;

    if (memchr(*buffer, '\0', length) != NULL) {
        return false;
    }

    if (length > 0U && (*buffer)[length - 1U] == '\n') {
        (*buffer)[length - 1U] = '\0';
    }

    return true;
}

static bool parse_count(const char *text, size_t *count)
{
    const char *start;
    char *end;
    uintmax_t value;

    if (text == NULL || count == NULL) {
        return false;
    }

    start = text;
    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return false;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || value > SIZE_MAX) {
        return false;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *count = (size_t)value;
    return true;
}

static bool parse_tuple(const char *text, int *first, int *second)
{
    const char *start;
    char *end;
    intmax_t first_value;
    intmax_t second_value;

    if (text == NULL || first == NULL || second == NULL) {
        return false;
    }

    start = text;
    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    errno = 0;
    first_value = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        first_value < INT_MIN || first_value > INT_MAX) {
        return false;
    }

    if (isspace((unsigned char)*end) == 0) {
        return false;
    }

    start = end;
    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    errno = 0;
    second_value = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        second_value < INT_MIN || second_value > INT_MAX) {
        return false;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *first = (int)first_value;
    *second = (int)second_value;
    return true;
}

int main(void)
{
    char *input = NULL;
    size_t input_capacity = 0U;
    Tuple *tuples = NULL;
    size_t count;
    size_t i;
    int status = EXIT_FAILURE;

    if (!read_line(&input, &input_capacity) ||
        !parse_count(input, &count)) {
        goto cleanup;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        goto cleanup;
    }

    if (count != 0U) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            goto cleanup;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (!read_line(&input, &input_capacity) ||
            !parse_tuple(input, &tuples[i].first, &tuples[i].second)) {
            goto cleanup;
        }

        tuples[i].frequency = 0U;
    }

    if (!assign_tuple_frequencies(tuples, count)) {
        goto cleanup;
    }

    for (i = 0U; i < count; ++i) {
        if (printf("(%d, %d) %zu\n",
                   tuples[i].first,
                   tuples[i].second,
                   tuples[i].frequency) < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    free(input);
    return status;
}