#include <stdio.h>
#include <stdlib.h>

int divide_tuples(const int *tuple1, const int *tuple2, double *result, size_t length)
{
    size_t i;

    if (tuple1 == NULL || tuple2 == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        if (tuple2[i] == 0) {
            return -2;
        }
        result[i] = (double)tuple1[i] / (double)tuple2[i];
    }

    return 0;
}

int main(void)
{
    int tuple1[] = {10, 4, 6, 9};
    /* Possible weaknesses found:
     *  Variable 'tuple2' can be declared as const array [constVariable]
     */
    int tuple2[] = {5, 6, 7, 5};
    size_t length = sizeof(tuple1) / sizeof(tuple1[0]);
    double *result;
    int status;
    size_t i;

    result = malloc(length * sizeof(double));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = divide_tuples(tuple1, tuple2, result, length);
    if (status == -1) {
        fprintf(stderr, "Invalid input pointers\n");
        free(result);
        return EXIT_FAILURE;
    }
    if (status == -2) {
        fprintf(stderr, "Division by zero detected\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Result: (");
    for (i = 0; i < length; i++) {
        printf("%f", result[i]);
        if (i < length - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    free(result);
    return EXIT_SUCCESS;
}