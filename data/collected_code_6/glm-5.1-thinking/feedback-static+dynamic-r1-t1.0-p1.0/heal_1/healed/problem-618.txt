#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

double *divide_lists(const double *a, const double *b, size_t size, int *error) {
    if (a == NULL || b == NULL || error == NULL) {
        if (error != NULL) {
            *error = EINVAL;
        }
        return NULL;
    }

    if (size == 0) {
        *error = 0;
        return NULL;
    }

    double *result = (double *)malloc(size * sizeof(double));
    if (result == NULL) {
        *error = ENOMEM;
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        if (b[i] == 0.0) {
            free(result);
            *error = EDOM;
            return NULL;
        }
        result[i] = a[i] / b[i];
    }

    *error = 0;
    return result;
}

int main(void) {
    double a[] = {10.0, 20.0, 30.0, 40.0, 50.0};
    const double b[] = {2.0, 4.0, 5.0, 8.0, 10.0};
    size_t size = sizeof(a) / sizeof(a[0]);
    int error = 0;

    double *result = divide_lists(a, b, size, &error);
    if (error != 0) {
        fprintf(stderr, "Error: %d\n", error);
        return EXIT_FAILURE;
    }

    if (result == NULL) {
        fprintf(stderr, "No result returned\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%.2f ", result[i]);
    }
    printf("\n");

    free(result);

    double c[] = {1.0, 2.0};
    const double d[] = {1.0, 0.0};
    size_t size2 = sizeof(c) / sizeof(c[0]);
    int error2 = 0;

    double *result2 = divide_lists(c, d, size2, &error2);
    if (error2 != 0) {
        fprintf(stderr, "Division error: %d\n", error2);
    }
    if (result2 != NULL) {
        free(result2);
    }

    int error3 = 0;
    (void)divide_lists(NULL, b, size, &error3);
    if (error3 != 0) {
        fprintf(stderr, "NULL input error: %d\n", error3);
    }

    return EXIT_SUCCESS;
}