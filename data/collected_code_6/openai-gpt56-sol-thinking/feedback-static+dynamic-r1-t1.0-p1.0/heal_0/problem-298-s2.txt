#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FIND_OK = 0,
    FIND_INVALID_ARGUMENT,
    FIND_SIZE_OVERFLOW,
    FIND_NO_MEMORY
} FindStatus;

static bool contains(const int *list, size_t length, int value)
{
    size_t i;

    for (i = 0; i < length; ++i) {
        if (list[i] == value) {
            return true;
        }
    }

    return false;
}

static FindStatus find_nested_list_elements(
    const int *const *nested_list,
    const size_t *nested_lengths,
    size_t nested_count,
    const int *other_list,
    size_t other_length,
    int **result,
    size_t *result_length)
{
    size_t i;
    size_t j;
    size_t match_count = 0;
    size_t result_index = 0;
    int *matches;

    if (result == NULL || result_length == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_length = 0;

    if ((nested_count > 0 && (nested_list == NULL || nested_lengths == NULL)) ||
        (other_length > 0 && other_list == NULL)) {
        return FIND_INVALID_ARGUMENT;
    }

    for (i = 0; i < nested_count; ++i) {
        if (nested_lengths[i] > 0 && nested_list[i] == NULL) {
            return FIND_INVALID_ARGUMENT;
        }

        for (j = 0; j < nested_lengths[i]; ++j) {
            if (contains(other_list, other_length, nested_list[i][j])) {
                if (match_count == SIZE_MAX) {
                    return FIND_SIZE_OVERFLOW;
                }
                ++match_count;
            }
        }
    }

    if (match_count == 0) {
        return FIND_OK;
    }

    if (match_count > SIZE_MAX / sizeof(*matches)) {
        return FIND_SIZE_OVERFLOW;
    }

    matches = malloc(match_count * sizeof(*matches));
    if (matches == NULL) {
        return FIND_NO_MEMORY;
    }

    for (i = 0; i < nested_count; ++i) {
        for (j = 0; j < nested_lengths[i]; ++j) {
            if (contains(other_list, other_length, nested_list[i][j])) {
                matches[result_index++] = nested_list[i][j];
            }
        }
    }

    *result = matches;
    *result_length = match_count;

    return FIND_OK;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6};
    const int third[] = {7, 8, 9};
    const int *nested_list[] = {first, second, third};
    const size_t nested_lengths[] = {
        sizeof(first) / sizeof(first[0]),
        sizeof(second) / sizeof(second[0]),
        sizeof(third) / sizeof(third[0])
    };
    const int other_list[] = {2, 4, 6, 8};
    int *result = NULL;
    size_t result_length = 0;
    size_t i;
    FindStatus status;

    status = find_nested_list_elements(
        nested_list,
        nested_lengths,
        sizeof(nested_list) / sizeof(nested_list[0]),
        other_list,
        sizeof(other_list) / sizeof(other_list[0]),
        &result,
        &result_length
    );

    if (status != FIND_OK) {
        fprintf(stderr, "Unable to find matching elements: error %d\n", status);
        free(result);
        return EXIT_FAILURE;
    }

    putchar('[');
    for (i = 0; i < result_length; ++i) {
        if (i > 0) {
            fputs(", ", stdout);
        }
        printf("%d", result[i]);
    }
    puts("]");

    free(result);
    return EXIT_SUCCESS;
}