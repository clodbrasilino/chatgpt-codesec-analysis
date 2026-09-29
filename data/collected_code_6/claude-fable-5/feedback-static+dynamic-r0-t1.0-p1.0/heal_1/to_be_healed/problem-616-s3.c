#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int tuple_modulo(const int *tuple1, const int *tuple2, int *result, size_t length)
{
    size_t i;

    if (tuple1 == NULL || tuple2 == NULL || result == NULL || length == 0U) {
        return -1;
    }

    for (i = 0U; i < length; i++) {
        if (tuple2[i] == 0) {
            return -1;
        }
        result[i] = tuple1[i] % tuple2[i];
    }

    return 0;
}

int main(void)
{
    int tuple1[] = { 10, 4, 5, 6 };
    /* Possible weaknesses found:
     *  Variable 'tuple2' can be declared as const array [constVariable]
     */
    int tuple2[] = { 5, 6, 7, 5 };
    size_t length = sizeof(tuple1) / sizeof(tuple1[0]);
    int *result;
    size_t i;
    int status;

    result = malloc(length * sizeof(*result));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = tuple_modulo(tuple1, tuple2, result, length);
    if (status != 0) {
        fprintf(stderr, "Modulo operation failed\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("(");
    for (i = 0U; i < length; i++) {
        if (i > 0U) {
            printf(", ");
        }
        printf("%d", result[i]);
    }
    printf(")\n");

    free(result);
    return EXIT_SUCCESS;
}