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
    if (tuple != NULL) {
        free(tuple->first);
        free(tuple->second);
        tuple->first = NULL;
        tuple->second = NULL;
    }
}

static int concatenate_strings(const char *left, const char *right, char **result)
{
    size_t left_length;
    size_t right_length;
    size_t allocation_size;
    char *buffer;

    if (left == NULL || right == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    left_length = strlen(left);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    right_length = strlen(right);

    if (left_length > SIZE_MAX - right_length ||
        left_length + right_length > SIZE_MAX - 1U) {
        return -1;
    }

    allocation_size = left_length + right_length + 1U;
    buffer = malloc(allocation_size);
    if (buffer == NULL) {
        return -1;
    }

    if (left_length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer, left, left_length);
    }

    if (right_length > 0U) {
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
    const StringTuple *right,
    StringTuple *result)
{
    StringTuple temporary = {NULL, NULL};

    if (left == NULL || right == NULL || result == NULL ||
        left->first == NULL || left->second == NULL ||
        right->first == NULL || right->second == NULL ||
        result == left || result == right) {
        return -1;
    }

    if (concatenate_strings(left->first, right->first,
                            &temporary.first) != 0) {
        return -1;
    }

    if (concatenate_strings(left->second, right->second,
                            &temporary.second) != 0) {
        free_string_tuple(&temporary);
        return -1;
    }

    *result = temporary;
    return 0;
}

int main(void)
{
    const StringTuple left = {"Hello, ", "Good "};
    const StringTuple right = {"world!", "morning!"};
    StringTuple result = {NULL, NULL};
    int status = EXIT_SUCCESS;

    if (concatenate_string_tuples(&left, &right, &result) != 0) {
        fputs("Failed to concatenate string tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("(\"%s\", \"%s\")\n", result.first, result.second) < 0) {
        status = EXIT_FAILURE;
    }

    free_string_tuple(&result);
    return status;
}