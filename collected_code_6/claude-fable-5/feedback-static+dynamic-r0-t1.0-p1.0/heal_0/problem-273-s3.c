#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int subtract_tuples(const int *tuple1, const int *tuple2, int *result, size_t length)
{
    size_t i;

    if (tuple1 == NULL || tuple2 == NULL || result == NULL || length == 0U) {
        return -1;
    }

    for (i = 0U; i < length; i++) {
        result[i] = tuple1[i] - tuple2[i];
    }

    return 0;
}

int main(void)
{
    const int tuple1[] = {10, 4, 5};
    const int tuple2[] = {2, 5, 18};
    const size_t length = sizeof(tuple1) / sizeof(tuple1[0]);
    int *result = NULL;
    size_t i;
    int status;

    result = malloc(length * sizeof(int));
    if (result == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = subtract_tuples(tuple1, tuple2, result, length);
    if (status != 0) {
        (void)fprintf(stderr, "Subtraction failed\n");
        free(result);
        return EXIT_FAILURE;
    }

    (void)printf("Result: (");
    for (i = 0U; i < length; i++) {
        if (i > 0U) {
            (void)printf(", ");
        }
        (void)printf("%d", result[i]);
    }
    (void)printf(")\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}