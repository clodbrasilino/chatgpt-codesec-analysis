#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *first;
    char *second;
} StringTuple;

static void free_string_tuple(StringTuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->first);
    free(tuple->second);
    tuple->first = NULL;
    tuple->second = NULL;
}

static int bounded_string_length(const char *string, size_t maximum, size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL) {
        return -1;
    }

    terminator = memchr(string, '\0', maximum);
    if (terminator == NULL) {
        return -1;
    }

    *length = (size_t)(terminator - string);
    return 0;
}

static int concatenate_strings(
    const char *left,
    size_t left_capacity,
    const char *right,
    size_t right_capacity,
    char **result)
{
    size_t left_length;
    size_t right_length;
    size_t allocation_size;
    char *buffer;

    if (left == NULL || right == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    if (bounded_string_length(left, left_capacity, &left_length) != 0 ||
        bounded_string_length(right, right_capacity, &right_length) != 0) {
        return -1;
    }

    if (right_length > SIZE_MAX - left_length ||
        left_length + right_length > SIZE_MAX - 1U) {
        return -1;
    }

    allocation_size = left_length + right_length + 1U;
    buffer = malloc(allocation_size);
    if (buffer == NULL) {
        return -1;
    }

    if (left_length != 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer, left, left_length);
    }

    if (right_length != 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer + left_length, right, right_length);
    }

    buffer[allocation_size - 1U] = '\0';
    *result = buffer;
    return 0;
}

static int concatenate_string_tuples(
    const StringTuple *left,
    size_t left_first_capacity,
    size_t left_second_capacity,
    const StringTuple *right,
    size_t right_first_capacity,
    size_t right_second_capacity,
    StringTuple *result)
{
    StringTuple temporary = {NULL, NULL};

    if (left == NULL || right == NULL || result == NULL ||
        left->first == NULL || left->second == NULL ||
        right->first == NULL || right->second == NULL ||
        result == left || result == right) {
        return -1;
    }

    if (concatenate_strings(
            left->first,
            left_first_capacity,
            right->first,
            right_first_capacity,
            &temporary.first) != 0) {
        return -1;
    }

    if (concatenate_strings(
            left->second,
            left_second_capacity,
            right->second,
            right_second_capacity,
            &temporary.second) != 0) {
        free_string_tuple(&temporary);
        return -1;
    }

    *result = temporary;
    return 0;
}

int main(void)
{
    static const char left_first[] = "Hello, ";
    static const char left_second[] = "Good ";
    static const char right_first[] = "world!";
    static const char right_second[] = "morning!";

    const StringTuple left = {
        (char *)left_first,
        (char *)left_second
    };
    const StringTuple right = {
        (char *)right_first,
        (char *)right_second
    };
    StringTuple result = {NULL, NULL};

    if (concatenate_string_tuples(
            &left,
            sizeof(left_first),
            sizeof(left_second),
            &right,
            sizeof(right_first),
            sizeof(right_second),
            &result) != 0) {
        fputs("Failed to concatenate string tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("(\"%s\", \"%s\")\n", result.first, result.second) < 0) {
        free_string_tuple(&result);
        return EXIT_FAILURE;
    }

    free_string_tuple(&result);
    return EXIT_SUCCESS;
}