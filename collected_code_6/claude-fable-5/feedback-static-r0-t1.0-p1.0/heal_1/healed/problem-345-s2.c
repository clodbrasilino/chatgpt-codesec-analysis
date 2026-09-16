#include <stdio.h>
#include <stdlib.h>

int compute_differences(const int *list, size_t n, int *diffs)
{
    size_t i;

    if (list == NULL || diffs == NULL || n < 2) {
        return -1;
    }

    for (i = 0; i < n - 1; i++) {
        diffs[i] = list[i + 1] - list[i];
    }

    return 0;
}

int main(void)
{
    int numbers[] = {10, 15, 7, 22, 30, 28};
    size_t n = sizeof(numbers) / sizeof(numbers[0]);
    int *diffs;
    size_t i;

    diffs = malloc((n - 1) * sizeof(*diffs));
    if (diffs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (compute_differences(numbers, n, diffs) != 0) {
        fprintf(stderr, "Failed to compute differences\n");
        free(diffs);
        return EXIT_FAILURE;
    }

    for (i = 0; i < n - 1; i++) {
        if (printf("Difference %zu: %d\n", i + 1, diffs[i]) < 0) {
            free(diffs);
            return EXIT_FAILURE;
        }
    }

    free(diffs);
    diffs = NULL;

    return EXIT_SUCCESS;
}