#include <stdio.h>
#include <math.h>

typedef struct {
    int numerator;
    int denominator;
} tuple_t;

double tuple_to_float(tuple_t t) {
    if (t.denominator == 0) {
        return NAN;
    }
    return (double)t.numerator / (double)t.denominator;
}

int main(void) {
    tuple_t t = {1, 2};
    double result = tuple_to_float(t);

    if (isnan(result)) {
        fprintf(stderr, "Error: division by zero\n");
        return 1;
    }

    printf("%f\n", result);
    return 0;
}