#include <stdio.h>
#include <stdlib.h>

int divide_lists(const double *list1, const double *list2, double *result, size_t length)
{
    size_t i;

    if (list1 == NULL || list2 == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        if (list2[i] == 0.0) {
            return -2;
        }
        result[i] = list1[i] / list2[i];
    }

    return 0;
}

int main(void)
{
    const double list1[] = {10.0, 20.0, 30.0, 40.0, 50.0};
    const double list2[] = {2.0, 4.0, 5.0, 8.0, 10.0};
    size_t length = sizeof(list1) / sizeof(list1[0]);
    double *result;
    int status;
    size_t i;

    result = malloc(length * sizeof(double));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = divide_lists(list1, list2, result, length);
    if (status == -1) {
        fprintf(stderr, "Invalid input: NULL pointer\n");
        free(result);
        return EXIT_FAILURE;
    }
    if (status == -2) {
        fprintf(stderr, "Division by zero detected\n");
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; i++) {
        printf("%f / %f = %f\n", list1[i], list2[i], result[i]);
    }

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}