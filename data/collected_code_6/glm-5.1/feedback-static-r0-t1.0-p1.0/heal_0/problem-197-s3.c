#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

typedef struct {
    double base;
    double exponent;
} Tuple;

int tuple_exp(const Tuple *input, double *result) {
    if (input == NULL || result == NULL) {
        errno = EFAULT;
        return -1;
    }

    errno = 0;
    double res = pow(input->base, input->exponent);

    if (errno == ERANGE) {
        return -1;
    }

    if (isnan(res) || isinf(res)) {
        errno = ERANGE;
        return -1;
    }

    *result = res;
    return 0;
}

int main(void) {
    Tuple t1 = {2.0, 10.0};
    Tuple t2 = {0.0, -1.0};
    Tuple t3 = {-4.0, 0.5};
    Tuple t4 = {10.0, 1000.0};

    double res = 0.0;

    if (tuple_exp(&t1, &res) == 0) {
        printf("%f ^ %f = %f\n", t1.base, t1.exponent, res);
    } else {
        printf("Error calculating t1 exponentiation\n");
    }

    if (tuple_exp(&t2, &res) == 0) {
        printf("%f ^ %f = %f\n", t2.base, t2.exponent, res);
    } else {
        printf("Error calculating t2 exponentiation\n");
    }

    if (tuple_exp(&t3, &res) == 0) {
        printf("%f ^ %f = %f\n", t3.base, t3.exponent, res);
    } else {
        printf("Error calculating t3 exponentiation\n");
    }

    if (tuple_exp(&t4, &res) == 0) {
        printf("%f ^ %f = %f\n", t4.base, t4.exponent, res);
    } else {
        printf("Error calculating t4 exponentiation\n");
    }

    if (tuple_exp(NULL, &res) == 0) {
        printf("NULL test = %f\n", res);
    } else {
        printf("Error calculating NULL exponentiation\n");
    }

    return 0;
}