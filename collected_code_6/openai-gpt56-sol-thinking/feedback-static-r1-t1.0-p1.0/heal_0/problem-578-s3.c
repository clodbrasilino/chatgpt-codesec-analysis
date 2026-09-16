#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int interleave_lists(const int *first, size_t first_length,
                     const int *second, size_t second_length,
                     int **output, size_t *output_length)
{
    size_t total_length;
    int *result;

    if (output == NULL || output_length == NULL) {
        return -1;
    }

    *output = NULL;
    *output_length = 0;

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

    total_length = first_length * 2;

    if (total_length > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(total_length * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < first_length; ++i) {
        result[i * 2] = first[i];
        result[i * 2 + 1] = second[i];
    }

    *output = result;
    *output_length = total_length;
    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4};
    const int second[] = {5, 6, 7, 8};
    const size_t first_length = sizeof(first) / sizeof(first[0]);
    const size_t second_length = sizeof(second) / sizeof(second[0]);
    int *interleaved = NULL;
    size_t interleaved_length = 0;

    if (interleave_lists(first, first_length, second, second_length,
                         &interleaved, &interleaved_length) != 0) {
        if (fprintf(stderr, "Failed to interleave lists\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < interleaved_length; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", interleaved[i]) < 0) {
            free(interleaved);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(interleaved);
        return EXIT_FAILURE;
    }

    free(interleaved);
    return EXIT_SUCCESS;
}