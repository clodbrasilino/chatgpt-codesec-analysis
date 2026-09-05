#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

int divide_tuples(Tuple a, Tuple b, double *result) {
    int denom_product = a.denominator * b.numerator;
    if (denom_product == 0) {
        return -1;
    }
    long long num_product = (long long)a.numerator * b.denominator;
    *result = (double)num_product / denom_product;
    return 0;
}

int main() {
    Tuple t1 = {10, 2};
    Tuple t2 = {3, 4};
    double res;

    if (divide_tuples(t1, t2, &res) != 0) {
        fprintf(stderr, "Division by zero\n");
        return EXIT_FAILURE;
    }

    printf("%lf\n", res);

    Tuple t3 = {5, 0};
    if (divide_tuples(t1, t3, &res) != 0) {
        fprintf(stderr, "Division by zero\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}