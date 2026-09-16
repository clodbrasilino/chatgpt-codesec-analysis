#include <stdio.h>
#include <stdlib.h>

int elementwise_and(const int *tuple1, const int *tuple2, int *result, size_t length)
{
    size_t i;

    if (tuple1 == NULL || tuple2 == NULL || result == NULL || length == 0U) {
        return -1;
    }

    for (i = 0U; i < length; i++) {
        result[i] = tuple1[i] & tuple2[i];
    }

    return 0;
}

int main(void)
{
    int tuple1[] = {10, 4, 6, 9};
    /* Possible weaknesses found:
     *  Variable 'tuple2' can be declared as const array [constVariable]
     */
    int tuple2[] = {5, 2, 3, 3};
    size_t length = sizeof(tuple1) / sizeof(tuple1[0]);
    int *result;
    size_t i;
    int status;

    result = (int *)malloc(length * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = elementwise_and(tuple1, tuple2, result, length);
    if (status != 0) {
        fprintf(stderr, "Invalid input to elementwise_and\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Tuple 1: (");
    for (i = 0U; i < length; i++) {
        printf("%d%s", tuple1[i], (i < length - 1U) ? ", " : "");
    }
    printf(")\n");

    printf("Tuple 2: (");
    for (i = 0U; i < length; i++) {
        printf("%d%s", tuple2[i], (i < length - 1U) ? ", " : "");
    }
    printf(")\n");

    printf("Elementwise AND: (");
    for (i = 0U; i < length; i++) {
        printf("%d%s", result[i], (i < length - 1U) ? ", " : "");
    }
    printf(")\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}