#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stddef.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

float tuple_to_float(const Tuple *t) {
    if (t == NULL) {
        errno = EINVAL;
        return NAN;
    }

    if (t->denominator != 0) {
        return (float)t->numerator / (float)t->denominator;
    }

    if (t->numerator == 0) {
        return 0.0f;
    }

    double num = fabs((double)t->numerator);
    double exponent = floor(log10(num));
    double divisor = pow(10.0, exponent);
    double result = num / divisor;

    return (float)(t->numerator < 0 ? -result : result);
}

int main(void) {
    Tuple t1 = {1, 2};
    Tuple t2 = {456, 0};
    Tuple t3 = {7256, 0};
    Tuple t4 = {8123, 0};

    errno = 0;
    float r1 = tuple_to_float(&t1);
    if (errno != 0) {
        fprintf(stderr, "Error converting tuple\n");
        return 1;
    }
    printf("%.6f\n", r1);

    errno = 0;
    float r2 = tuple_to_float(&t2);
    if (errno != 0) {
        fprintf(stderr, "Error converting tuple\n");
        return 1;
    }
    printf("%.6f\n", r2);

    errno = 0;
    float r3 = tuple_to_float(&t3);
    if (errno != 0) {
        fprintf(stderr, "Error converting tuple\n");
        return 1;
    }
    printf("%.6f\n", r3);

    errno = 0;
    float r4 = tuple_to_float(&t4);
    if (errno != 0) {
        fprintf(stderr, "Error converting tuple\n");
        return 1;
    }
    printf("%.6f\n", r4);

    return 0;
}