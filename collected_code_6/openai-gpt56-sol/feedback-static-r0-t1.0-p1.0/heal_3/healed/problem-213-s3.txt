#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} StringTuple;

static void free_string_tuple(StringTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->first);
        free(tuple->second);
        tuple->first = NULL;
        tuple->second = NULL;
    }
}

static int concatenate_strings(const char *left, size_t left_length,
                               const char *right, size_t right_length,
                               char **result)
{
    size_t content_length;
    char *buffer;

    if (left == NULL || right == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    if (left_length > SIZE_MAX - right_length) {
        return -1;
    }

    content_length = left_length + right_length;

    if (content_length == SIZE_MAX) {
        return -1;
    }

    buffer = malloc(content_length + 1U);
    if (buffer == NULL) {
        return -1;
    }

    if (left_length > 0U) {
        memmove(buffer, left, left_length);
    }

    if (right_length > 0U) {
        memmove(buffer + left_length, right, right_length);
    }

    buffer[content_length] = '\0';
    *result = buffer;

    return 0;
}

static int concatenate_string_tuples(
    const StringTuple *left,
    const size_t left_lengths[2],
    const StringTuple *right,
    const size_t right_lengths[2],
    StringTuple *result)
{
    StringTuple temporary = {NULL, NULL};

    if (left == NULL || left_lengths == NULL ||
        right == NULL || right_lengths == NULL ||
        result == NULL ||
        left->first == NULL || left->second == NULL ||
        right->first == NULL || right->second == NULL ||
        result == left || result == right) {
        return -1;
    }

    if (concatenate_strings(left->first, left_lengths[0],
                            right->first, right_lengths[0],
                            &temporary.first) != 0) {
        return -1;
    }

    if (concatenate_strings(left->second, left_lengths[1],
                            right->second, right_lengths[1],
                            &temporary.second) != 0) {
        free_string_tuple(&temporary);
        return -1;
    }

    free_string_tuple(result);
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
    const size_t left_lengths[2] = {
        sizeof(left_first) - 1U,
        sizeof(left_second) - 1U
    };
    const size_t right_lengths[2] = {
        sizeof(right_first) - 1U,
        sizeof(right_second) - 1U
    };
    StringTuple result = {NULL, NULL};
    int status = EXIT_SUCCESS;

    if (concatenate_string_tuples(&left, left_lengths,
                                  &right, right_lengths,
                                  &result) != 0) {
        fputs("Failed to concatenate string tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("(\"%s\", \"%s\")\n", result.first, result.second) < 0) {
        status = EXIT_FAILURE;
    }

    free_string_tuple(&result);
    return status;
}