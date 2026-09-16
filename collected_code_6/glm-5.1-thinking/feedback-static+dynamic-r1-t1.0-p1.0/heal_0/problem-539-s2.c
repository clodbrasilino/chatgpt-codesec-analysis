#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

typedef double (*BinaryOp)(double, double);

double power_op(double base, double index) {
    errno = 0;
    double res = pow(base, index);
    if (errno != 0 || isnan(res) || isinf(res)) {
        return NAN;
    }
    return res;
}

double* map(const double* bases, const double* indices, size_t length, BinaryOp op) {
    if (bases == NULL || indices == NULL || op == NULL || length == 0) {
        return NULL;
    }
    double* result = malloc(length * sizeof(double));
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < length; i++) {
        result[i] = op(bases[i], indices[i]);
    }
    return result;
}

int main(void) {
    double bases[] = {2.0, 3.0, 4.0, 5.0};
    double indices[] = {3.0, 2.0, 0.5, 1.0};
    size_t length = sizeof(bases) / sizeof(bases[0]);

    double* result = map(bases, indices, length, power_op);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; i++) {
        printf("%f\n", result[i]);
    }

    free(result);

    return EXIT_SUCCESS;
}