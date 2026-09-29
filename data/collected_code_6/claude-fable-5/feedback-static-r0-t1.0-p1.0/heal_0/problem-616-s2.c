#include <stdio.h>
#include <stdlib.h>

int tuple_modulo(const int *tuple1, const int *tuple2, int *result, size_t length)
{
    size_t i;

    if (tuple1 == NULL || tuple2 == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        if (tuple2[i] == 0) {
            return -1;
        }
        result[i] = tuple1[i] % tuple2[i];
    }

    return 0;
}

int main(void)
{
    int tuple1[] = {10, 4, 5, 6};
    int tuple2[] = {5, 6, 7, 5};
    size_t length = sizeof(tuple1) / sizeof(tuple1[0]);
    int *result;
    size_t i;

    result = malloc(length * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (tuple_modulo(tuple1, tuple2, result, length) != 0) {
        fprintf(stderr, "Error: invalid input or division by zero\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("(");
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