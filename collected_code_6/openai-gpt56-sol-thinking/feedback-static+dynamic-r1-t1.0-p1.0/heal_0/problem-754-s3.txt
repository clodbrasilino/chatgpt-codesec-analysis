#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t index;
    int value;
} CommonIndexElement;

typedef enum {
    FIND_SUCCESS = 0,
    FIND_INVALID_ARGUMENT,
    FIND_INSUFFICIENT_CAPACITY
} FindResult;

FindResult find_common_index_elements(
    const int *first,
    size_t first_length,
    const int *second,
    size_t second_length,
    const int *third,
    size_t third_length,
    CommonIndexElement *output,
    size_t output_capacity,
    size_t *output_count)
{
    size_t length;
    size_t count = 0;
    int count_only;

    if (output_count == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *output_count = 0;
    length = first_length;

    if (second_length < length) {
        length = second_length;
    }

    if (third_length < length) {
        length = third_length;
    }

    if (length > 0 && (first == NULL || second == NULL || third == NULL)) {
        return FIND_INVALID_ARGUMENT;
    }

    count_only = output == NULL && output_capacity == 0;

    if (output == NULL && output_capacity > 0) {
        return FIND_INVALID_ARGUMENT;
    }

    for (size_t index = 0; index < length; ++index) {
        if (first[index] == second[index] && second[index] == third[index]) {
            if (!count_only && count < output_capacity) {
                output[count].index = index;
                output[count].value = first[index];
            }
            ++count;
        }
    }

    *output_count = count;

    if (!count_only && count > output_capacity) {
        return FIND_INSUFFICIENT_CAPACITY;
    }

    return FIND_SUCCESS;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5, 6};
    const int second[] = {1, 8, 3, 9, 5, 0};
    const int third[] = {1, 7, 3, 4, 5, 2};
    const size_t first_length = sizeof first / sizeof first[0];
    const size_t second_length = sizeof second / sizeof second[0];
    const size_t third_length = sizeof third / sizeof third[0];
    CommonIndexElement *matches = NULL;
    size_t match_count = 0;
    FindResult result;
    int exit_status = EXIT_SUCCESS;

    result = find_common_index_elements(
        first,
        first_length,
        second,
        second_length,
        third,
        third_length,
        NULL,
        0,
        &match_count);

    if (result != FIND_SUCCESS) {
        fputs("Unable to count common index elements.\n", stderr);
        return EXIT_FAILURE;
    }

    if (match_count > SIZE_MAX / sizeof *matches) {
        fputs("Result size is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (match_count > 0) {
        matches = malloc(match_count * sizeof *matches);

        if (matches == NULL) {
            fputs("Unable to allocate result storage.\n", stderr);
            return EXIT_FAILURE;
        }

        result = find_common_index_elements(
            first,
            first_length,
            second,
            second_length,
            third,
            third_length,
            matches,
            match_count,
            &match_count);

        if (result != FIND_SUCCESS) {
            fputs("Unable to find common index elements.\n", stderr);
            free(matches);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < match_count; ++i) {
        if (printf("Index %zu: %d\n", matches[i].index, matches[i].value) < 0) {
            exit_status = EXIT_FAILURE;
            break;
        }
    }

    if (fflush(stdout) == EOF) {
        exit_status = EXIT_FAILURE;
    }

    free(matches);
    return exit_status;
}