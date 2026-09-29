#include <stdio.h>
#include <math.h>

typedef struct {
    int num;
    int den;
} Tuple;

double tuple_to_float(Tuple t) {
    if (t.den == 0) {
        return NAN;
    }
    return (double)t.num / (double)t.den;
}

int main(void) {
    Tuple t1 = {22, 7};
    Tuple t2 = {5, 0};

    double r1 = tuple_to_float(t1);
    double r2 = tuple_to_float(t2);

    printf("%f\n", r1);

    if (isnan(r2)) {
        printf("NaN\n");
    } else {
        printf("%f\n", r2);
    }

    return 0;
}