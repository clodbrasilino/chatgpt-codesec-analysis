#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_CAPACITY 256U

typedef struct {
    int first;
    int second;
    size_t frequency;
} Tuple;

typedef struct {
    int first;
    int second;
    size_t index;
} TupleKey;

static int compare_tuple_keys(const void *left_ptr, const void *right_ptr)
{
    const TupleKey *left = left_ptr;
    const TupleKey *right = right_ptr;

    if (left->first < right->first) {
        return -1;
    }
    if (left->first > right->first) {
        return 1;
    }
    if (left->second < right->second) {
        return -1;
    }
    if (left->second > right->second) {
        return 1;
    }

    return 0;
}

bool assign_tuple_frequencies(Tuple *tuples, size_t count)
{
    TupleKey *keys;
    size_t i;

    if (tuples == NULL && count != 0U) {
        return false;
    }

    if (count == 0U) {
        return true;
    }

    if (count > SIZE_MAX / sizeof(*keys)) {
        return false;
    }

    keys = malloc(count * sizeof(*keys));
    if (keys == NULL) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        keys[i].first = tuples[i].first;
        keys[i].second = tuples[i].second;
        keys[i].index = i;
    }

    qsort(keys, count, sizeof(*keys), compare_tuple_keys);

    i = 0U;
    while (i < count) {
        size_t end = i + 1U;
        size_t j;

        while (end < count &&
               keys[end].first == keys[i].first &&
               keys[end].second == keys[i].second) {
            ++end;
        }

        for (j = i; j < end; ++j) {
            tuples[keys[j].index].frequency = end - i;
        }

        i = end;
    }

    free(keys);
    return true;
}

static bool read_line(char *buffer, size_t capacity)
{
    char *newline;

    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        return true;
    }

    return feof(stdin) != 0;
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
    Tuple *tuples = NULL;
    size_t count;
    size_t i;
    int status = EXIT_FAILURE;

    input = malloc(INPUT_CAPACITY);
    if (input == NULL) {
        goto cleanup;
    }

    if (!read_line(input, INPUT_CAPACITY) ||
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
        if (!read_line(input, INPUT_CAPACITY) ||
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