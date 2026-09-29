#include <stdio.h>
#include <stdlib.h>

int pairwise_addition(const int *tuple, size_t size, int *result)
{
    size_t i;

    if (tuple == NULL || result == NULL || size < 2U) {
        return -1;
    }

    for (i = 0U; i < size - 1U; i++) {
        result[i] = tuple[i] + tuple[i + 1U];
    }

    return 0;
}

int main(void)
{
    int tuple[] = {1, 5, 7, 8, 10};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    int *result;
    size_t i;
    int status;

    result = malloc((size - 1U) * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = pairwise_addition(tuple, size, result);
    if (status != 0) {
        fprintf(stderr, "Pairwise addition failed\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Pairwise addition result: ");
    for (i = 0U; i < size - 1U; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}