#include <stdio.h>
#include <stdlib.h>

int subtract_tuples(const int *a, const int *b, int *result, size_t len)
{
    size_t i;

    if (a == NULL || b == NULL || result == NULL || len == 0U) {
        return -1;
    }

    for (i = 0U; i < len; i++) {
        result[i] = a[i] - b[i];
    }

    return 0;
}

int main(void)
{
    int tuple1[] = { 10, 20, 30, 40, 50 };
    int tuple2[] = { 1, 2, 3, 4, 5 };
    size_t len = sizeof(tuple1) / sizeof(tuple1[0]);
    int *result;
    size_t i;
    int status;

    result = malloc(len * sizeof(*result));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = subtract_tuples(tuple1, tuple2, result, len);
    if (status != 0) {
        fprintf(stderr, "Subtraction failed\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Result: (");
    for (i = 0U; i < len; i++) {
        printf("%d", result[i]);
        if (i < len - 1U) {
            printf(", ");
        }
    }
    printf(")\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}