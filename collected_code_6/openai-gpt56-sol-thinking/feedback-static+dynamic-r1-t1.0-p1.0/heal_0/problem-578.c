#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int interleave_lists(const int *first, size_t first_length,
                     const int *second, size_t second_length,
                     int **result, size_t *result_length)
{
    size_t combined_length;
    int *interleaved;

    if (result == NULL || result_length == NULL) {
        return -1;
    }

    *result = NULL;
    *result_length = 0;

    if (first_length != second_length) {
        return -1;
    }

    if (first_length == 0) {
        return 0;
    }

    if (first == NULL || second == NULL) {
        return -1;
    }

    if (first_length > SIZE_MAX / 2) {
        return -1;
    }

    combined_length = first_length * 2;

    if (combined_length > SIZE_MAX / sizeof(*interleaved)) {
        return -1;
    }

    interleaved = malloc(combined_length * sizeof(*interleaved));
    if (interleaved == NULL) {
        return -1;
    }

    for (size_t i = 0; i < first_length; ++i) {
        interleaved[2 * i] = first[i];
        interleaved[2 * i + 1] = second[i];
    }

    *result = interleaved;
    *result_length = combined_length;
    return 0;
}

int main(void)
{
    const int first[] = {1, 3, 5, 7};
    const int second[] = {2, 4, 6, 8};
    const size_t first_length = sizeof(first) / sizeof(first[0]);
    const size_t second_length = sizeof(second) / sizeof(second[0]);
    int *result = NULL;
    size_t result_length = 0;

    if (interleave_lists(first, first_length, second, second_length,
                         &result, &result_length) != 0) {
        fputs("Failed to interleave lists.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_length; ++i) {
        if (printf("%d%s", result[i], i + 1 == result_length ? "\n" : " ") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}