#include <stdio.h>
#include <stdlib.h>

int elementwise_and(const int *tuple1, const int *tuple2, int *result, size_t size)
{
    size_t i;

    if (tuple1 == NULL || tuple2 == NULL || result == NULL || size == 0U) {
        return -1;
    }

    for (i = 0U; i < size; i++) {
        result[i] = tuple1[i] & tuple2[i];
    }

    return 0;
}

int main(void)
{
    int tuple1[] = {10, 4, 6, 9};
    int tuple2[] = {5, 2, 3, 3};
    size_t size = sizeof(tuple1) / sizeof(tuple1[0]);
    int *result;
    size_t i;

    result = (int *)malloc(size * sizeof(int));
    if (result == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (elementwise_and(tuple1, tuple2, result, size) != 0) {
        (void)fprintf(stderr, "Invalid input to elementwise_and\n");
        free(result);
        return EXIT_FAILURE;
    }

    (void)printf("(");
    for (i = 0U; i < size; i++) {
        (void)printf("%d", result[i]);
        if (i < (size - 1U)) {
            (void)printf(", ");
        }
    }
    (void)printf(")\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}