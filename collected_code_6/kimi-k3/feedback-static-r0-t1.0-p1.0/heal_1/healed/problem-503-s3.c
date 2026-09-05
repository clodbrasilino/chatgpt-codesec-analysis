#include <stdio.h>
#include <stdlib.h>

void add_consecutive(const int *list, size_t size, int *result, size_t *result_size)
{
    if (size == 0) {
        *result_size = 0;
        return;
    }

    *result_size = size - 1;

    for (size_t i = 0; i < *result_size; i++) {
        result[i] = list[i] + list[i + 1];
    }
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(list) / sizeof(list[0]);
    int *result = NULL;
    size_t result_size = 0;

    result = (int *)malloc((size - 1) * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    add_consecutive(list, size, result, &result_size);

    printf("Original list: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    printf("Consecutive sums: ");
    for (size_t i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}