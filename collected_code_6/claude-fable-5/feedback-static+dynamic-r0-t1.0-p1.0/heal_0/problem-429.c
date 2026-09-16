#include <stdio.h>
#include <stdlib.h>

int elementwise_and(const int *tuple1, const int *tuple2, int *result, size_t length)
{
    size_t i;

    if (tuple1 == NULL || tuple2 == NULL || result == NULL) {
        return -1;
    }

    if (length == 0) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        result[i] = tuple1[i] & tuple2[i];
    }

    return 0;
}

int main(void)
{
    int tuple1[] = {10, 4, 6, 9};
    int tuple2[] = {5, 2, 3, 3};
    size_t length = sizeof(tuple1) / sizeof(tuple1[0]);
    int *result;
    size_t i;

    result = malloc(length * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (elementwise_and(tuple1, tuple2, result, length) != 0) {
        fprintf(stderr, "Invalid input to elementwise_and\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Elementwise AND result: (");
    for (i = 0; i < length; i++) {
        printf("%d", result[i]);
        if (i < length - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    free(result);
    return EXIT_SUCCESS;
}