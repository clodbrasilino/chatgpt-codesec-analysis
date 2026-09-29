#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool interleave_lists(const int *first, const int *second, size_t length,
                      int **result, size_t *result_length)
{
    size_t combined_length;
    int *interleaved;

    if (result == NULL || result_length == NULL) {
        return false;
    }

    *result = NULL;
    *result_length = 0U;

    if (length == 0U) {
        return true;
    }

    if (first == NULL || second == NULL) {
        return false;
    }

    if (length > SIZE_MAX / 2U) {
        return false;
    }

    combined_length = length * 2U;

    if (combined_length > SIZE_MAX / sizeof(*interleaved)) {
        return false;
    }

    interleaved = malloc(combined_length * sizeof(*interleaved));
    if (interleaved == NULL) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        interleaved[2U * i] = first[i];
        interleaved[2U * i + 1U] = second[i];
    }

    *result = interleaved;
    *result_length = combined_length;

    return true;
}

int main(void)
{
    const int first[] = {1, 3, 5, 7};
    const int second[] = {2, 4, 6, 8};
    const size_t length = sizeof(first) / sizeof(first[0]);
    int *result = NULL;
    size_t result_length = 0U;

    if (!interleave_lists(first, second, length, &result, &result_length)) {
        fputs("Failed to interleave lists.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < result_length; ++i) {
        printf("%d%s", result[i], i + 1U == result_length ? "\n" : " ");
    }

    free(result);

    return EXIT_SUCCESS;
}