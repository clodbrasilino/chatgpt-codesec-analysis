#include <stdio.h>
#include <stdlib.h>

int compute_differences(const int *list, size_t length, int *result)
{
    size_t i;

    if (list == NULL || result == NULL || length < 2U) {
        return -1;
    }

    for (i = 0U; i < length - 1U; i++) {
        result[i] = list[i + 1U] - list[i];
    }

    return 0;
}

int main(void)
{
    int numbers[] = {3, 8, 15, 23, 42, 50};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int *differences;
    size_t i;

    differences = malloc((length - 1U) * sizeof(int));
    if (differences == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (compute_differences(numbers, length, differences) != 0) {
        fprintf(stderr, "Invalid input to compute_differences\n");
        free(differences);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < length - 1U; i++) {
        printf("Difference between %d and %d: %d\n",
               numbers[i], numbers[i + 1U], differences[i]);
    }

    free(differences);
    return EXIT_SUCCESS;
}